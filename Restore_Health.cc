#include "Restore_Health.h"
using namespace std;

Restore_Health::Restore_Health(int x, int y, Floor *f) :
	Potion(x, y, f, "RH") {};

void Restore_Health::UseOnPC() {
	int cur_hp = plyer->getHp();
	int base = 10;
	if (plyer->getRace() == "Drow") {
		base = base * 1.5;
	}
	if (cur_hp + base >= plyer->getMaxHp()) {
		plyer->setHp(plyer->getMaxHp());
	}
	else {
		plyer->setHp(cur_hp + base);
	}
}

