#ifndef ITEM_H
#define ITEM_H
#include "unit.h"

class Player;
class Item : public Unit {
protected:
	Player * plyer;
public:
	//std::string getName();
	Item(int, int, char, std::string, Floor *);
	void setPlayer(Player *);
};
#endif


