#ifndef CHARACTER_H
#define CHARACTER_H
#include "unit.h"

class Character :public Unit {
protected:
	int hp;
	int def;
	int atk;
	int Max_Hp;
	std::string race;
	int oldX;
	int oldY;
public:
	int getHp();
	int getDef();
	int getAtk();
	int getMaxHp();
	void setHp(int);
	void setDef(int);
	void setAtk(int);
	std::string getRace();
	//virtual void attack() = 0;
	Character(int, int, char, std::string ,Floor *,int,int,int,std::string);
	~Character();

};

#endif



