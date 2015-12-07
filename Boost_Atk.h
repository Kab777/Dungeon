#ifndef BOOST_ATK
#define BOOST_ATK
#include "potion.h"
class Boost_Atk :public Potion {
public:
	Boost_Atk(int x, int y, Floor *f);
	void UseOnPC();
};
#endif

