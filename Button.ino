#include <Joystick.h>

#include "Button.h"

void Button::press(int index) {
	Joystick.setButton(index, 1);
}

void Button::release(int index) {
	Joystick.setButton(index, 0);
}
