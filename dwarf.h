#ifndef DWARF_H
#define DWARF_H
#include "enemy.h"

class Dwarf :public Enemy {
public:
	Dwarf(int x, int y, char c_type, Floor *f);
};
#endif



