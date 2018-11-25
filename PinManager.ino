#include "PinManager.h"

void PinManager::setup(PinManagerEvent *event) {
	for(int i = 0; i < digitalKeyMatrixRowNum; i++) {
		pinMode(digitalKeyMatrixRowPin[i], OUTPUT);
	}
	for(int i = 0; i < digitalkeyMatrixColNum; i++) {
		pinMode(digitalKeyMatrixColPin[i], INPUT_PULLUP);
	}
	for(int i = 0; i < digitalNum; i++) {
		pinMode(digitalPin[i], INPUT_PULLUP);
	}
	for(int i = 0; i < analogDeviceNum; i++) {
		for(int j = 0; j < analogPinNum; j++) {
			pinMode(analogPin[i][j], INPUT);
		}
	}

	for( int i = 0; i < digitalKeyMatrixRowNum; i++){
		for( int j = 0; j < digitalkeyMatrixColNum; j++){
			currentState[i][j] = HIGH;
			previousState[i][j] = HIGH;
		}
		digitalWrite(digitalKeyMatrixRowPin[i], HIGH);
	}
	for(int i = 0; i < digitalNum; i++) {
		currentDigitalState[i] = HIGH;
		previousDigitalState[i] = HIGH;
	}
	for(int i = 0; i < analogDeviceNum; i++) {
		for(int j = 0; j < analogPinNum; j++) {
			currentAnalogValue[i][j] = 0;
			previousAnalogValue[i][j] = 0;
		}
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

	for(int i = 0; i < digitalNum; i++) {
		currentDigitalState[i] = digitalRead(digitalPin[i]);

		if(currentDigitalState[i] != previousDigitalState[i]) {

			event->onDigitalReadChange(i, currentDigitalState[i]);

			previousDigitalState[i] = currentDigitalState[i];
		}
	}

	for(int i = 0; i < analogDeviceNum; i++) {
		for(int j = 0; j < analogPinNum; j++) {
			currentAnalogValue[i][j] = analogRead(analogPin[i][j]);

			int a = currentAnalogValue[i][j] - previousAnalogValue[i][j];

			if(a < (analogCalibrate * -1) || analogCalibrate < a) {
				event->onAnalogReadChange(i, j, currentAnalogValue[i][j]);

				previousAnalogValue[i][j] = currentAnalogValue[i][j];
			}
		}
	}
}
