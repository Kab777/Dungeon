#ifndef POISON_HEALTH
#define POISON_HEALTH
#include "potion.h"

class Poison_Health :public Potion{
public:
	Poison_Health(int x, int y, Floor *f);
	void UseOnPC();
};
#endif


