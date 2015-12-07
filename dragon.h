#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"


class Dragon_Hoard;
class Dragon :public Enemy {
	Dragon_Hoard *guard;
public:
	Dragon(int x, int y, char c_type, Floor *f);
	Dragon(int x, int y, char c_type, Floor *f, Dragon_Hoard *DH);
	void move();
	void Iamdead();
	void setGuard(Dragon_Hoard *);
};

#endif


