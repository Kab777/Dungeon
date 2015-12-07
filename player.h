#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include <iostream>

class Player :public Character {
protected:
	int gold;
	std::string action;
public:
	Player(int x, int y,Floor *f, int, int, int, std::string r_type);
	virtual bool move(std::string direction);
	int getGold();
	virtual void attack(std::string e_type);
	int getAttacked(int dmg, std::string e_type);
	void changeGold(int);
	virtual ~Player();
	std::string getAction();
	void setAction(std::string add);
};





class Shade :public Player {
public:
	Shade(int x, int y  ,Floor *f, int hp, int def, int atk)
		:Player(x, y,f, hp, def, atk, "Shade") {};
};

class Drow :public Player {
public:
	Drow(int x, int y  ,Floor *f, int hp, int def, int atk)
		:Player(x, y,f, hp, def, atk, "Drow") {};
};

class Vampire :public Player {
public:
	Vampire(int x, int y  ,Floor *f, int hp, int def, int atk)
		:Player(x, y,f, hp, def, atk, "Vampire") {};
	void attack(std::string e_type) {
		int base = 5;
		if (e_type == "Dwarf") {
			std::cout << "vampire loeses 5 hp" << std::endl;
			setHp(getHp() - base);
		}
		else {
			std::cout << "vampire gains 5 hp" << std::endl;
			setHp(getHp() + base);
		}
	}
};
class Troll :public Player {
public:
	Troll(int x, int y  ,Floor *f, int hp, int def, int atk)
		:Player(x, y,f, hp, def, atk, "Troll") {};
	void attack(std::string e_type) {
		setHp(hp + 5);
	}
};
class Goblin :public Player {
public:
	Goblin(int x, int y  ,Floor *f, int hp, int def, int atk)
		:Player(x, y,f, hp, def, atk, "Goblin") {};
	void attack(std::string e_type) {
		int base = 5;
		changeGold(base);
	}
};

#endif

