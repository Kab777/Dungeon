#include "Wound_Def.h"
using namespace std;

Wound_Def::Wound_Def(int x, int y, Floor *f) :
	Potion(x, y, f, "WD") {};

void Wound_Def::UseOnPC() {
	int cur_def = plyer->getDef();
	int base = 5;
	if (plyer->getRace() == "Drow") {
		base = base * 1.5;
	}
	plyer->setDef(cur_def - base);
}
