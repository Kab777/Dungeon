#ifndef WOUND_ATK
#define WOUND_ATK
#include "potion.h"
class Wound_Atk :public Potion{
public:
	Wound_Atk(int x, int y, Floor *f);
	void UseOnPC();
};
#endif


