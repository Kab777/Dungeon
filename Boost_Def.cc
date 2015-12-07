#include "Boost_Def.h"
using namespace std;

Boost_Def::Boost_Def(int x, int y, Floor *f) :
	Potion(x, y, f, "BD") {};

void Boost_Def::UseOnPC() {
	int cur_def = plyer->getDef();
	int base = 5;
	if (plyer->getRace() == "Drow") {
		base = base * 1.5;
	}
	plyer->setDef(cur_def + base);
}


