#include "Poison_Health.h"

using namespace std;

Poison_Health::Poison_Health(int x, int y, Floor *f) :
	Potion(x, y, f, "PH"){};

void Poison_Health::UseOnPC() {
	int cur_hp =plyer->getHp();
	int base = 10;
	if (plyer->getRace() == "Drow") {
		base = base * 1.5;
	}
	if ((cur_hp - base) <= 0) {
		cur_hp = 1;
	}
	plyer->setHp(cur_hp - base);
}
