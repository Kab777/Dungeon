#ifndef SMALL_GOLD
#define SMALL_GOLD
#include "Treasure.h"
class Small_Gold :public Treasure{
public:
	Small_Gold(int x, int y, Floor *f);
	void UseOnPc();
};
#endif

