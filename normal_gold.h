#ifndef NORMAL_GOLD
#define NORMAL_GOLD
#include "Treasure.h"

class Normal_Gold:public Treasure{
public:
	Normal_Gold(int x, int y, Floor *f);
	void UseOnPc();
};
#endif

