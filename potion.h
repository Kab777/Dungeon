#ifndef POTION_H
#define POTION_H
#include "item.h"
#include "player.h"

class Potion :public Item {
	std::string P_name;
public:
	Potion(int x, int y, Floor *f, std::string potion_name);
	virtual void UseOnPC() = 0;
	std::string getPname();
};
#endif


