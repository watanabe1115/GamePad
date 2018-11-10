#include <Joystick.h>

#include "POV.h"

typedef void (*ButtonEvent)();

const int rowNum = 2;
const int colNum = 5;
const int rowPin[rowNum] = { 14, 15 };
const int colPin[colNum] = { 2, 3, 4, 5, 6 };
ButtonEvent ***joystickButtonEvent;

// 現在のdigitalRead値
int currentState[rowNum][colNum];
// 一つ前のdigitalRead値
int previousState[rowNum][colNum];

// Set Joystick Config
Joystick_ Joystick(
	JOYSTICK_DEFAULT_REPORT_ID,
	JOYSTICK_TYPE_GAMEPAD,
	1,                                // Button Count
	JOYSTICK_DEFAULT_HATSWITCH_COUNT, // Hat Switch Count
	true, true, false,                // X and Y, but no Z Axis
	false, false, false,              // No Rx, Ry, or Rz
	false, false,                     // No rudder or throttle
	false, false, false               // No accelerator, brake, or steering
);

void setup() {
	InitializePins();

	Serial.begin(9600);

	// Initialize Joystick Library
	Joystick.begin();
	Joystick.setXAxisRange(-1, 1);
	Joystick.setYAxisRange(-1, 1);

	RegisterJoystickEvent();
}

void loop() {
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

				// 登録された各ボタンのイベントを実行
				if(joystickButtonEvent[ currentState[i][j] ][i][j] != NULL) {
					joystickButtonEvent[ currentState[i][j] ][i][j]();
				}

				previousState[i][j] = currentState[i][j];
			}
		}

		digitalWrite(rowPin[i], HIGH);
	}
}


/**
 * PINの初期化を行う
 */
void InitializePins() {
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

/**
 * ボタンを押した際の処理を登録します
 * LOW 時に押され、HIGH時に離されます
 */
void RegisterJoystickEvent() {
	joystickButtonEvent = new ButtonEvent**[2];
	for(int i = 0; i < 2; i++) {
		joystickButtonEvent[i] = new ButtonEvent*[rowNum];
		for(int j = 0; j < rowNum; j++) {
			joystickButtonEvent[i][j] = new ButtonEvent[colNum];
			for(int k = 0; k < colNum; k++) {
				joystickButtonEvent[i][j][k] = NULL;
			}
		}
	}
	joystickButtonEvent[LOW][0][0] = pressPOVUp;
	joystickButtonEvent[LOW][0][1] = pressPOVDown;
	joystickButtonEvent[LOW][0][2] = pressPOVLeft;
	joystickButtonEvent[LOW][0][3] = pressPOVRight;
	joystickButtonEvent[HIGH][0][0] = releasePOVUp;
	joystickButtonEvent[HIGH][0][1] = releasePOVDown;
	joystickButtonEvent[HIGH][0][2] = releasePOVLeft;
	joystickButtonEvent[HIGH][0][3] = releasePOVRight;
}