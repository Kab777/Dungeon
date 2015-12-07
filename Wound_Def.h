#ifndef WOUND_DEF
#define WOUND_DEF
#include "potion.h"
class Wound_Def :public Potion {
public:
	Wound_Def(int x, int y, Floor *f);
	void UseOnPC();
};
#endif

