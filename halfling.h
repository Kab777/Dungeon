#ifndef HALFLING_H
#define HALFLING_H
#include "enemy.h"


class Halfling:public Enemy {
public:
	Halfling(int x, int y, char c_type, Floor *f);
	int getAttacked(int dmg, std::string race);
};

#endif


