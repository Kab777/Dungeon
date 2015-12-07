#include "human.h"
#include <string>
using namespace std;

Human::Human(int x, int y, char c_type, Floor *f)
	:Enemy(x, y, c_type, f, 140,20,20, "Human", true) {};
