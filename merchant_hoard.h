#ifndef MERCHANT_HOARD
#define MERCHANT_HOARD
#include "Treasure.h"

class Merchant_Hoard :public Treasure{
public:
	Merchant_Hoard(int x, int y, Floor *f);
	void UseOnPc();
};
#endif

