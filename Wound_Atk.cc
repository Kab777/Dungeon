#include "Wound_Atk.h"
using namespace std;

Wound_Atk::Wound_Atk(int x, int y, Floor *f) :
	Potion(x, y, f, "WA") {};

void Wound_Atk::UseOnPC() {
	int cur_atk = plyer->getAtk();
	int base = 5;
	if (plyer->getRace() == "Drow") {
		base = base * 1.5;
	}
	plyer->setAtk(cur_atk - base);
}
