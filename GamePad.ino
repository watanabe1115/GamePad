#include <Joystick.h>

#include "GamePad.h"

// #define DUALSHOCK4_BUTTON_NUM 14
// // Set Joystick Config
// Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, DUALSHOCK4_BUTTON_NUM, JOYSTICK_DEFAULT_HATSWITCH_COUNT, true, true, true, true, true, true, false, false, false, false, false);

GamePad *pad = new GamePad();

void setup() {
	Serial.begin(9600);

	pad->setup(GamePad::PadKind::DUALSHOCK4);
}

void loop() {
	pad->loop();
}
