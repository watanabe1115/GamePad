#pragma once

class POV {
private:
	const int HatSwitchNo = 0;
	char pressedPOV = 0x00;

public:
	static const char Up = 0x01;
	static const char Down = 0x02;
	static const char Left = 0x04;
	static const char Right = 0x08;

	void press(char press);
	void release(char release);
	void update();
};

