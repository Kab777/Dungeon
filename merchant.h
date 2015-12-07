#ifndef MERCHANT_H
#define MERCHANT_H

#include "enemy.h"


class Merchant :public Enemy {
public:
	Merchant(int x, int y, char c_type, Floor *f);
	int getAttacked(int dmg, std::string race);
};

#endif

