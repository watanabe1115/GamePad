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

	Joystick.setXAxisRange(0, 1024);
	Joystick.setYAxisRange(0, 1024);
	Joystick.setZAxisRange(0, 1024);
	Joystick.setRzAxisRange(0, 1024);
}

void GamePad::loop()
{
	pinManager.loop();
}

void GamePad::onDigitalReadChange(int pinIndex, int status)
{
	// Serial.print("onDigitalReadChange (");
	// Serial.print(row);
	// Serial.print(", ");
	// Serial.print(col);
	// Serial.print(", ");
	// Serial.print(status);
	// Serial.println(")");
}
void GamePad::onDigitalReadChange(int rowPinIndex, int colPinIndex, int status)
{
	// Serial.print("onDigitalReadChange (");
	// Serial.print(row);
	// Serial.print(", ");
	// Serial.print(col);
	// Serial.print(", ");
	// Serial.print(status);
	// Serial.println(")");

	if(isPOV(rowPinIndex, colPinIndex)) {
		POV(rowPinIndex, colPinIndex, status);
	}

	if(isButton(rowPinIndex, colPinIndex)) {
		Button(rowPinIndex, colPinIndex, status);
	}
}
void GamePad::onAnalogReadChange(int pinIndex, int value)
{
	// Serial.print("onDigitalReadChange (");
	// Serial.print(deviceNo);
	// Serial.print(", ");
	// Serial.print(pinNo);
	// Serial.print(", ");
	// Serial.print(value);
	// Serial.println(")");

	Stick(pinIndex, value);
}


void GamePad::setupPadButton(PadKind kind)
{
	switch(kind) {
		case PadKind::DUALSHOCK4:
		{
			keyMatrixButtonName[0][0] = ButtonName::POV_UP;
			keyMatrixButtonName[0][1] = ButtonName::POV_DOWN;
			keyMatrixButtonName[0][2] = ButtonName::POV_LEFT;
			keyMatrixButtonName[0][3] = ButtonName::POV_RIGHT;

			keyMatrixButtonName[1][0] = ButtonName::PLAYSTATION_SQUARE;
			keyMatrixButtonName[1][1] = ButtonName::PLAYSTATION_CROSS;
			keyMatrixButtonName[1][2] = ButtonName::PLAYSTATION_CIRCLE;
			keyMatrixButtonName[1][3] = ButtonName::PLAYSTATION_TRIANGLE;
		}
		break;
	}
}

bool GamePad::isPOV(int row, int col)
{
	ButtonName name = keyMatrixButtonName[row][col];
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
	ButtonName name = keyMatrixButtonName[row][col];
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

bool GamePad::isButton(int row, int col)
{
	ButtonName name = keyMatrixButtonName[row][col];
	switch(name) {
		case ButtonName::PLAYSTATION_SQUARE:
		case ButtonName::PLAYSTATION_CROSS:
		case ButtonName::PLAYSTATION_CIRCLE:
		case ButtonName::PLAYSTATION_TRIANGLE:
		case ButtonName::SWITCH_Y:
		case ButtonName::SWITCH_B:
		case ButtonName::SWITCH_A:
		case ButtonName::SWITCH_X:
		case ButtonName::XBOX_X:
		case ButtonName::XBOX_A:
		case ButtonName::XBOX_B:
		case ButtonName::XBOX_Y:
		return true;
		break;
	}
	return false;
}
void GamePad::Button(int row, int col, int status)
{
	ButtonName name = keyMatrixButtonName[row][col];
	int value = 0;
	if(status == LOW) {
		value = 1;
	} else if(status == HIGH) {
		value = 0;
	}

	switch(name) {
		case ButtonName::PLAYSTATION_SQUARE:
		case ButtonName::SWITCH_Y:
		case ButtonName::XBOX_X:
		{
			Joystick.setButton(0, value);
		}
		break;
		case ButtonName::PLAYSTATION_CROSS:
		case ButtonName::SWITCH_B:
		case ButtonName::XBOX_A:
		{
			Joystick.setButton(1, value);
		}
		break;
		case ButtonName::PLAYSTATION_CIRCLE:
		case ButtonName::SWITCH_A:
		case ButtonName::XBOX_B:
		{
			Joystick.setButton(2, value);
		}
		break;
		case ButtonName::PLAYSTATION_TRIANGLE:
		case ButtonName::SWITCH_X:
		case ButtonName::XBOX_Y:
		{
			Joystick.setButton(3, value);
		}
		break;
	}
}

void GamePad::Stick(int pinIndex, int value)
{
	if(value > CenterStickValue - StickCalibrate && value < CenterStickValue + StickCalibrate) {
		value = CenterStickValue;
	}

	switch(pinIndex) {
		case 0:
			Joystick.setXAxis(value);
		break;
		case 1:
			Joystick.setYAxis(value);
		break;
		case 2:
			Joystick.setZAxis(value);
		break;
		case 3:
			Joystick.setRzAxis(value);
		break;
	}
}
