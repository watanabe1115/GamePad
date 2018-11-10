#include <Joystick.h>

#include "POV.h"

void POV::press(char press) {
	pressedPOV |= press;
	update();
}

void POV::release(char release) {
	pressedPOV &= ~release;
	update();
}

/**
 * POVの値を更新する
 */
void POV::update() {
	switch(pressedPOV) {
		case Up:
			Joystick.setHatSwitch(HatSwitchNo, 0);
		break;
		case Up | Left:
			Joystick.setHatSwitch(HatSwitchNo, 315);
		break;
		case Up | Right:
			Joystick.setHatSwitch(HatSwitchNo, 45);
		break;
		case Left:
			Joystick.setHatSwitch(HatSwitchNo, 270);
		break;
		case Right:
			Joystick.setHatSwitch(HatSwitchNo, 90);
		break;
		case Down:
			Joystick.setHatSwitch(HatSwitchNo, 180);
		break;
		case Down | Left:
			Joystick.setHatSwitch(HatSwitchNo, 225);
		break;
		case Down | Right:
			Joystick.setHatSwitch(HatSwitchNo, 135);
		break;
		default:
			Joystick.setHatSwitch(HatSwitchNo, -1);
		break;
	}
}
