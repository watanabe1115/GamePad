#pragma once

class PinManagerEvent {
public:
	virtual void onDigitalReadChange(int pinIndex, int state);
	virtual void onDigitalReadChange(int rowPinIndex, int colPinIndex, int status);
	virtual void onAnalogReadChange(int deviceNum, int pinIndex, int value);
};


class PinManager {
public:
	static const int digitalKeyMatrixRowNum = 3;
	static const int digitalkeyMatrixColNum = 5;
	static const int digitalNum = 2;
	static const int analogDeviceNum = 2;
	static const int analogPinNum = 2;

private:
	const int digitalKeyMatrixRowPin[digitalKeyMatrixRowNum]{14, 15, 16};
	const int digitalKeyMatrixColPin[digitalkeyMatrixColNum]{2, 3, 4, 5, 6};
	const int digitalPin[digitalNum]{8, 9};
	const int analogPin[analogDeviceNum][analogPinNum]{ {A0, A1},{A2, A3} };

	// 現在のdigitalRead値
	int currentState[digitalKeyMatrixRowNum][digitalkeyMatrixColNum];
	// 一つ前のdigitalRead値
	int previousState[digitalKeyMatrixRowNum][digitalkeyMatrixColNum];

	int currentDigitalState[digitalNum];
	int previousDigitalState[digitalNum];

	int currentAnalogValue[analogDeviceNum][analogPinNum];
	int previousAnalogValue[analogDeviceNum][analogPinNum];

	// この値以下の変動は無視されます.
	const int analogCalibrate = 4;
	

	PinManagerEvent *event;

public:

	void setup(PinManagerEvent *event);
	void loop();
};
