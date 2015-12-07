#ifndef TREASURE_H
#define TREASURE_H
#include "item.h"
#include "player.h"
class Treasure :public Item {
protected:
	int value;
	bool edible;
	std::string T_name;
public:
	Treasure(int x, int y, Floor *f, std::string Treasure_name, int value, bool ed = true);
	int getValue();
	virtual void UseOnPc() = 0;
	std::string getT_name();
	void changeEdible();
	bool getEdible();
};
#endif


