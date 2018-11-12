#include <Joystick.h>

#include "PinManager.h"
#include "POV.h"

#define DUALSHOCK4_BUTTON_NUM 14

typedef void (*ButtonEvent)();
ButtonEvent ***joystickButtonEvent;

// Set Joystick Config
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, DUALSHOCK4_BUTTON_NUM, JOYSTICK_DEFAULT_HATSWITCH_COUNT, true, true, true, true, true, true, false, false, false, false, false);

PinManager pinManager;

void setup() {
	pinManager.setup();
	pinManager.onDigitalReadChange = onDigitalReadValueChange;

	Serial.begin(9600);

	// Initialize Joystick Library
	Joystick.begin();
	Joystick.setXAxisRange(-1, 1);
	Joystick.setYAxisRange(-1, 1);

	RegisterJoystickEvent();
}

void loop() {
	pinManager.loop();
}

void onDigitalReadValueChange(int LOW_or_HIGH, int i, int j) {
	// 登録された各ボタンのイベントを実行
	if(joystickButtonEvent[ LOW_or_HIGH ][i][j] != NULL) {
		joystickButtonEvent[ LOW_or_HIGH ][i][j]();
	}
}

/**
 * ボタンを押した際の処理を登録します
 * LOW 時に押され、HIGH時に離されます
 */
void RegisterJoystickEvent() {
	joystickButtonEvent = new ButtonEvent**[2];
	for(int i = 0; i < 2; i++) {
		joystickButtonEvent[i] = new ButtonEvent*[PinManager::rowNum];
		for(int j = 0; j < PinManager::rowNum; j++) {
			joystickButtonEvent[i][j] = new ButtonEvent[PinManager::colNum];
			for(int k = 0; k < PinManager::colNum; k++) {
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
	joystickButtonEvent[LOW][1][0] = pressButton1;
	joystickButtonEvent[HIGH][1][0] = releaseButton1;
	joystickButtonEvent[LOW][1][1] = pressButton2;
	joystickButtonEvent[HIGH][1][1] = releaseButton2;
}