#ifndef HUMAN_H
#define HUMAN_H
#include "enemy.h"

class Human :public Enemy {
public:
	Human(int x, int y, char c_type, Floor *f);
};

#endif
