#include "dwarf.h"
using namespace std;

Dwarf::Dwarf(int x, int y, char c_type, Floor *f)
	:Enemy(x, y, c_type, f, 100, 30, 20, "Dwarf", true) {};

