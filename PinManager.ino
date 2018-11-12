#include "PinManager.h"

void PinManager::setup() {
	for(int i = 0; i < rowNum; i++) {
		pinMode(rowPin[i], OUTPUT);
	}
	for(int i = 0; i < colNum; i++) {
		pinMode(colPin[i], INPUT_PULLUP);
	}

	for( int i = 0; i < rowNum; i++){
		for( int j = 0; j < colNum; j++){
			currentState[i][j] = HIGH;
			previousState[i][j] = HIGH;
		}
		digitalWrite(rowPin[i], HIGH);
	}
}

void PinManager::loop() {
	for(int i = 0; i < rowNum; i++) {
		digitalWrite(rowPin[i], LOW);

		for(int j = 0; j < colNum; j++) {
			currentState[i][j] = digitalRead(colPin[j]);

			if(currentState[i][j] != previousState[i][j]) {

				// Serial.print("key(");
				// Serial.print(currentState[i][j]);
				// Serial.print(",");
				// Serial.print(i);
				// Serial.print(",");
				// Serial.print(j);
				// Serial.print(")");
				// Serial.println(" ");

				if(onDigitalReadChange) {
					onDigitalReadChange(currentState[i][j], i, j);
				}

				previousState[i][j] = currentState[i][j];
			}
		}

		digitalWrite(rowPin[i], HIGH);
	}
}