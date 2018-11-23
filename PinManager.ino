#include "PinManager.h"

void PinManager::setup(PinManagerEvent *event) {
	for(int i = 0; i < rowNum; i++) {
		pinMode(rowPin[i], OUTPUT);
	}
	for(int i = 0; i < colNum; i++) {
		pinMode(colPin[i], INPUT_PULLUP);
	}
	for(int i = 0; i < analogDeviceNum; i++) {
		for(int j = 0; j < analogPinNum; j++) {
			pinMode(analogPin[i][j], INPUT);
		}
	}

	for( int i = 0; i < rowNum; i++){
		for( int j = 0; j < colNum; j++){
			currentState[i][j] = HIGH;
			previousState[i][j] = HIGH;
		}
		digitalWrite(rowPin[i], HIGH);
	}

	for(int i = 0; i < analogDeviceNum; i++) {
		for(int j = 0; j < analogPinNum; j++) {
			currentAnalogValue[i][j] = 0;
			previousAnalogValue[i][j] = 0;
		}
	}

	pinMode(16, OUTPUT);
	digitalWrite(16, HIGH);

	this->event = event;
}

void PinManager::loop() {
	for(int i = 0; i < rowNum; i++) {
		digitalWrite(rowPin[i], LOW);

		for(int j = 0; j < colNum; j++) {
			currentState[i][j] = digitalRead(colPin[j]);

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

		digitalWrite(rowPin[i], HIGH);
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
