#include <Joystick.h>
#include "GamePad.h"

#define DUALSHOCK4_BUTTON_NUM 14
// Set Joystick Config
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, DUALSHOCK4_BUTTON_NUM, JOYSTICK_DEFAULT_HATSWITCH_COUNT, true, true, true, true, true, true, false, false, false, false, false);

void GamePad::setup(PadKind padKind)
{
	// Joystick = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, DUALSHOCK4_BUTTON_NUM, JOYSTICK_DEFAULT_HATSWITCH_COUNT, true, true, true, true, true, true, false, false, false, false, false);
	Joystick.begin();
	pinManager.setup(this);

	setupPadButton(padKind);
}

void GamePad::loop()
{
	pinManager.loop();
}


void GamePad::onDigitalReadChange(int row, int col, int status)
{
	// Serial.print("onDigitalReadChange (");
	// Serial.print(row);
	// Serial.print(", ");
	// Serial.print(col);
	// Serial.print(", ");
	// Serial.print(status);
	// Serial.println(")");

	if(isPOV(row, col)) {
		POV(row, col, status);
	}
}
void GamePad::onAnalogReadChange(int i, int j, int value)
{
	// Serial.print("onAnalogReadChange (");
	// Serial.print(i);
	// Serial.print(", ");
	// Serial.print(j);
	// Serial.print(", ");
	// Serial.print(value);
	// Serial.println(")");
}


void GamePad::setupPadButton(PadKind kind)
{
	switch(kind) {
		case PadKind::DUALSHOCK4:
		{
			buttonPIN[0][0] = ButtonName::POV_UP;
			buttonPIN[0][1] = ButtonName::POV_DOWN;
			buttonPIN[0][2] = ButtonName::POV_LEFT;
			buttonPIN[0][3] = ButtonName::POV_RIGHT;
		}
		break;
	}
}

bool GamePad::isPOV(int row, int col)
{
	ButtonName name = buttonPIN[row][col];
	switch(name) {
		case ButtonName::POV_UP:
		case ButtonName::POV_DOWN:
		case ButtonName::POV_LEFT:
		case ButtonName::POV_RIGHT:
		return true;
		break;
	}
	return false;
}
void GamePad::POV(int row, int col, int status)
{
	PovDirection p = PovDirection::NONE;
	ButtonName name = buttonPIN[row][col];
	switch(name) {
		case ButtonName::POV_UP:
		{
			p = PovDirection::UP;
		}
		break;
		case ButtonName::POV_DOWN:
		{
			p = PovDirection::DOWN;
		}
		break;
		case ButtonName::POV_LEFT:
		{
			p = PovDirection::LEFT;
		}
		break;
		case ButtonName::POV_RIGHT:
		{
			p = PovDirection::RIGHT;
		}
		break;
	}

	if(status == LOW) {
		// Press POV Button.
		pressedPOV |= static_cast<char>(p);
	} else if(status == HIGH) {
		// Release POV Button.
		pressedPOV &= ~static_cast<int>(p);
	}
	updatePOV();
}
void GamePad::updatePOV()
{
	Serial.println((int)pressedPOV);
	switch(pressedPOV) {
		case static_cast<char>(PovDirection::UP):
			Joystick.setHatSwitch(HatSwitchNo, 0);
		break;
		case static_cast<char>(PovDirection::UP) | static_cast<char>(PovDirection::LEFT):
			Joystick.setHatSwitch(HatSwitchNo, 315);
		break;
		case static_cast<char>(PovDirection::UP) | static_cast<char>(PovDirection::RIGHT):
			Joystick.setHatSwitch(HatSwitchNo, 45);
		break;
		case static_cast<char>(PovDirection::LEFT):
			Joystick.setHatSwitch(HatSwitchNo, 270);
		break;
		case static_cast<char>(PovDirection::RIGHT):
			Joystick.setHatSwitch(HatSwitchNo, 90);
		break;
		case static_cast<char>(PovDirection::DOWN):
			Joystick.setHatSwitch(HatSwitchNo, 180);
		break;
		case static_cast<char>(PovDirection::DOWN) | static_cast<char>(PovDirection::LEFT):
			Joystick.setHatSwitch(HatSwitchNo, 225);
		break;
		case static_cast<char>(PovDirection::DOWN) | static_cast<char>(PovDirection::RIGHT):
			Joystick.setHatSwitch(HatSwitchNo, 135);
		break;
		default:
			Joystick.setHatSwitch(HatSwitchNo, -1);
		break;
	}
}

void GamePad::isButton(int row, int col)
{
	ButtonName name = buttonPIN[row][col];
}
