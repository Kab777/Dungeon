#ifndef ORCS_H
#define ORCS_H
#include "enemy.h"


class Orcs :public Enemy {
public:
	Orcs(int x, int y, char c_type, Floor *f);
};

#endif


