#pragma once

class PinManagerEvent {
public:
	virtual void onDigitalReadChange(int i, int j, int status);
	virtual void onAnalogReadChange(int i, int j, int value);
};


class PinManager {
public:
	static const int rowNum = 2;
	static const int colNum = 5;
	static const int analogDeviceNum = 2;
	static const int analogPinNum = 2;

private:
	const int digitalKeyMatrixRowPin[rowNum]{14, 15};
	const int digitalKeyMatrixColPin[colNum]{2, 3, 4, 5, 6};
	const int analogPin[analogDeviceNum][analogPinNum]{ {A0, A1},{A2, A3} };

	// 現在のdigitalRead値
	int currentState[rowNum][colNum];
	// 一つ前のdigitalRead値
	int previousState[rowNum][colNum];

	int currentAnalogValue[analogDeviceNum][analogPinNum];
	int previousAnalogValue[analogDeviceNum][analogPinNum];

	// この値以下の変動は無視されます.
	const int analogCalibrate = 4;
	

	PinManagerEvent *event;

public:

	void setup(PinManagerEvent *event);
	void loop();
};
