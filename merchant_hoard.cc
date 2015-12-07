#include "merchant_hoard.h"

using namespace std;

Merchant_Hoard::Merchant_Hoard(int x, int y, Floor *f) :
	Treasure(x, y, f, "MH", 4) {};

void Merchant_Hoard::UseOnPc() {
	int base = value;
	plyer->changeGold(base);
}
