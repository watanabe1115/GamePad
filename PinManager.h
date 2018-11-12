#pragma once

class PinManager {
public:
	static const int rowNum = 2;
	static const int colNum = 5;

private:
	const int rowPin[rowNum]{14, 15};
	const int colPin[colNum]{2, 3, 4, 5, 6};

	// 現在のdigitalRead値
	int currentState[rowNum][colNum];
	// 一つ前のdigitalRead値
	int previousState[rowNum][colNum];


public:
	void (*onDigitalReadChange)(int, int, int);

	void setup();
	void loop();
};
