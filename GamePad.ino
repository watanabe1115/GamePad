#include <Joystick.h>

#include "GamePad.h"

GamePad *pad = new GamePad();

void setup() {
	Serial.begin(9600);

	pad->setup(GamePad::PadKind::DUALSHOCK4);
}

void loop() {
	pad->loop();
}
