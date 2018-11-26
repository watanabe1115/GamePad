#include "PinManager.h"

void PinManager::setup(PinManagerEvent *event) {
	for(int i = 0; i < digitalKeyMatrixRowNum; i++) {
		pinMode(digitalKeyMatrixRowPin[i], OUTPUT);
	}
	for(int i = 0; i < digitalkeyMatrixColNum; i++) {
		pinMode(digitalKeyMatrixColPin[i], INPUT_PULLUP);
	}
	for(int i = 0; i < digitalPinNum; i++) {
		pinMode(digitalPin[i], INPUT_PULLUP);
	}
	for(int i = 0; i < analogPinNum; i++) {
		pinMode(analogPin[i], INPUT);
	}

	for( int i = 0; i < digitalKeyMatrixRowNum; i++){
		for( int j = 0; j < digitalkeyMatrixColNum; j++){
			currentState[i][j] = HIGH;
			previousState[i][j] = HIGH;
		}
		digitalWrite(digitalKeyMatrixRowPin[i], HIGH);
	}
	for(int i = 0; i < digitalPinNum; i++) {
		currentDigitalState[i] = HIGH;
		previousDigitalState[i] = HIGH;
	}
	for(int i = 0; i < analogPinNum; i++) {
			currentAnalogValue[i] = 0;
			previousAnalogValue[i] = 0;
	}

	this->event = event;
}

void PinManager::loop() {
	for(int i = 0; i < digitalKeyMatrixRowNum; i++) {
		digitalWrite(digitalKeyMatrixRowPin[i], LOW);

		for(int j = 0; j < digitalkeyMatrixColNum; j++) {
			currentState[i][j] = digitalRead(digitalKeyMatrixColPin[j]);

			if(currentState[i][j] != previousState[i][j]) {

				Serial.print("key(");
				Serial.print(currentState[i][j]);
				Serial.print(",");
				Serial.print(i);
				Serial.print(",");
				Serial.print(j);
				Serial.print(")");
				Serial.println(" ");

				event->onDigitalReadChange(i, j, currentState[i][j]);

				previousState[i][j] = currentState[i][j];
			}
		}

		digitalWrite(digitalKeyMatrixRowPin[i], HIGH);
	}

	for(int i = 0; i < digitalPinNum; i++) {
		currentDigitalState[i] = digitalRead(digitalPin[i]);

		if(currentDigitalState[i] != previousDigitalState[i]) {

			event->onDigitalReadChange(i, currentDigitalState[i]);

			previousDigitalState[i] = currentDigitalState[i];
		}
	}

	for(int i = 0; i < analogPinNum; i++) {
		currentAnalogValue[i] = analogRead(analogPin[i]);

		int diff = currentAnalogValue[i] - previousAnalogValue[i];

		if(diff < (analogCalibrate * -1) || analogCalibrate < diff) {

			event->onAnalogReadChange(i, currentAnalogValue[i]);

			previousAnalogValue[i] = currentAnalogValue[i];
		}
	}
}
