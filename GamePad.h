#pragma once

#include "PinManager.h"
#include "ButtonName.h"

using namespace Constants;

class GamePad : PinManagerEvent {
public:
	enum class PadKind {
		DUALSHOCK4,
		JOYCON,
		XBOX
	};

	void setup(PadKind padKind);
	void loop();

	void onDigitalReadChange(int row, int col, int status);
	void onAnalogReadChange(int i, int j, int value);
private:

	enum class PovDirection {
		NONE = 0,
		UP = 1, 
		DOWN = 2,
		LEFT = 4,
		RIGHT = 8
	};
	static const int HatSwitchNo = 0;

	/// 各ボタンの対応するPIN番号
	ButtonName keyMatrixButtonName[PinManager::rowNum][PinManager::colNum];

	PinManager pinManager;

	PadKind padKind;

	char pressedPOV = 0x00;

	void setupPadButton(PadKind kind);


	bool isPOV(int row, int col);
	void POV(int row, int col, int status);
	void updatePOV();

	bool isButton(int row, int col);
	void Button(int row, int col, int status);

};
