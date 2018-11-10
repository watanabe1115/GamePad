#include <Joystick.h>

#include "POV.h"

char pressedPOV = 0x00;

const int HatSwitchNo = 0;

/**
 * POVの値を更新する
 */
void update(char pressPOV) {
	switch(pressPOV) {
		case static_cast<char>(E_POV::Up):
			Joystick.setHatSwitch(HatSwitchNo, 0);
		break;
		case static_cast<char>(E_POV::Up) | static_cast<char>(E_POV::Left):
			Joystick.setHatSwitch(HatSwitchNo, 315);
		break;
		case static_cast<char>(E_POV::Up) | static_cast<char>(E_POV::Right):
			Joystick.setHatSwitch(HatSwitchNo, 45);
		break;
		case static_cast<char>(E_POV::Left):
			Joystick.setHatSwitch(HatSwitchNo, 270);
		break;
		case static_cast<char>(E_POV::Right):
			Joystick.setHatSwitch(HatSwitchNo, 90);
		break;
		case static_cast<char>(E_POV::Down):
			Joystick.setHatSwitch(HatSwitchNo, 180);
		break;
		case static_cast<char>(E_POV::Down) | static_cast<char>(E_POV::Left):
			Joystick.setHatSwitch(HatSwitchNo, 225);
		break;
		case static_cast<char>(E_POV::Down) | static_cast<char>(E_POV::Right):
			Joystick.setHatSwitch(HatSwitchNo, 135);
		break;
		default:
			Joystick.setHatSwitch(HatSwitchNo, -1);
		break;
	}
}

void press(E_POV p) {
	pressedPOV |= static_cast<char>(p);
	update(pressedPOV);
}
void release(E_POV r) {
	pressedPOV &= ~static_cast<char>(r);
	update(pressedPOV);
}

void pressPOVUp() {
	press(E_POV::Up);
}
void pressPOVDown() {
	press(E_POV::Down);
}
void pressPOVLeft() {
	press(E_POV::Left);
}
void pressPOVRight() {
	press(E_POV::Right);
}
void releasePOVUp() {
	release(E_POV::Up);
}
void releasePOVDown() {
	release(E_POV::Down);
}
void releasePOVLeft() {
	release(E_POV::Left);
}
void releasePOVRight() {
	release(E_POV::Right);
}