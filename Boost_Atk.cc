#include "Boost_Atk.h"
using namespace std;

Boost_Atk::Boost_Atk(int x, int y, Floor *f) :
	Potion(x, y, f, "BA") {};

void Boost_Atk::UseOnPC() {
	int cur_atk = plyer->getAtk();
	int base = 5;
	if (plyer->getRace() == "Drow") {
		base = base * 1.5;
	}
	plyer->setAtk(cur_atk + base);
}
