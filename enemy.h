#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include <cstdlib>

class Enemy :public Character {
protected:
	bool hostile;
	bool isPlayer;// if whether there is player within a block
public:
	Enemy(int x, int y, char c_type, Floor *f, int, int, int, std::string r_type, bool is_hostile);
	void attack(int dmg, std::string e_type);
	virtual void move();
	void detect();
	virtual int getAttacked(int dmg, std::string race);
	virtual ~Enemy();
	void changeHostility();
};

#endif



