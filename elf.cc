#include "elf.h"
using namespace std;

Elf::Elf(int x, int y, char c_type, Floor *f)
	:Enemy(x, y, c_type, f, 140, 10, 30, "Elf", true) {};

