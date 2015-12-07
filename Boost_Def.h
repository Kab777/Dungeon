#ifndef BOOST_DEF
#define BOOST_DEF
#include "potion.h"
class Boost_Def :public Potion {
public:
	Boost_Def(int x, int y, Floor *f);
	void UseOnPC();
};
#endif

