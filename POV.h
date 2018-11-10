#pragma once

enum class E_POV {
	Up = 0x01,
	Down = 0x02,
	Left = 0x04,
	Right = 0x08,
};

void pressPOVUp();
void pressPOVDown();
void pressPOVLeft();
void pressPOVRight();
void releasePOVUp();
void releasePOVDown();
void releasePOVLeft();
void releasePOVRight();
