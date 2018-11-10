#include "POV.h"

POV *pov = new POV();

void pressPOVUp() {
	pov->press(POV::Up);
}
void pressPOVDown() {
	pov->press(POV::Down);
}
void pressPOVLeft() {
	pov->press(POV::Left);
}
void pressPOVRight() {
	pov->press(POV::Right);
}
void releasePOVUp() {
	pov->release(POV::Up);
}
void releasePOVDown() {
	pov->release(POV::Down);
}
void releasePOVLeft() {
	pov->release(POV::Left);
}
void releasePOVRight() {
	pov->release(POV::Right);
}
