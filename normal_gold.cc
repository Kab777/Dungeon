#include "normal_gold.h"
using namespace std;
Normal_Gold::Normal_Gold(int x, int y, Floor *f) :
	Treasure(x, y, f, "NG", 2) {};

void Normal_Gold::UseOnPc() {
	int base = value;
	plyer->changeGold(base);
}

