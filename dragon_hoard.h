#ifndef DRAGON_HOARD
#define DRAGON_HOARD
#include "Treasure.h"
#include "floor.h"
#include <cstdlib>
#include <vector>

class Dragon_Hoard:public Treasure{
	std::vector<MyPair> ava_cord;
	void addcord();
	//int Dra_x;
	//int Dra_y;
public:
	Dragon_Hoard(int x, int y, Floor *f);
	MyPair getRanCor();
	Dragon_Hoard * getDH();
	void UseOnPc();
	//void FindDra();
};
#endif


