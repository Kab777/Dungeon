#include "orcs.h"
using namespace std;

Orcs::Orcs(int x, int y, char c_type, Floor *f)
	:Enemy(x, y, c_type, f, 180, 25, 30, "Orcs", true) {};
