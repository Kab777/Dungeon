#include "small_gold.h"

using namespace std;
Small_Gold::Small_Gold(int x, int y, Floor *f) :
	Treasure(x, y, f, "SG", 1) {};

void Small_Gold::UseOnPc() {
	int base = value;
	plyer->changeGold(base);
}

