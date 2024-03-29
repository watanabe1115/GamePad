#pragma once

#include "PinManager.h"

#include "PovDirection.h"
#include "ButtonName.h"

using namespace GamePadConstants;

class GamePad : PinManagerEvent {
public:
	enum class PadKind {
		DUALSHOCK4,
		JOYCON,
		XBOX
	};

	void setup(PadKind padKind);
	void loop();

	void onDigitalReadChange(int pinIndex, int state);
	void onDigitalReadChange(int rowPinIndex, int colPinIndex, int status);
	void onAnalogReadChange(int pinIndex, int value);
private:

	static const int HatSwitchNo = 0;

	static const int MinStickValue = 0;
	static const int MaxStickValue = 1024;
	static const int StickCalibrate = 64;
	static const int CenterStickValue = (MinStickValue + MaxStickValue) / 2;


	/// 各ボタンの対応するPIN番号
	ButtonName keyMatrixButtonName[PinManager::digitalKeyMatrixRowNum][PinManager::digitalkeyMatrixColNum];
	ButtonName digitalButtonName[PinManager::digitalPinNum];

	PinManager pinManager;

	PadKind padKind;

	char pressedPOV = 0x00;

	void setupKeyMatrixButton(PadKind kind);
	void setupDigitalButton(PadKind kind);


	bool isPOV(int row, int col);
	void POV(int row, int col, int status);
	void updatePOV();

	bool isButton(int row, int col);
	void Button(int row, int col, int status);

	void Stick(int pinIndex, int value);
	void StickButton(int pinIndex, int value);
};
