#include "Treasure.h"
using namespace std;

Treasure::Treasure(int x, int y, Floor *f, std::string Trea_name, int my_value, bool ed)
	: Item(x, y, 'G', "Treasure", f),value(my_value),T_name(Trea_name), edible(ed) {};

int Treasure::getValue() {
	return value;
}
std::string Treasure::getT_name() {
	return T_name;
}

void Treasure::changeEdible() {
	if (edible == false) {
		edible = true;
	}
	else {
		edible = false;
	}
}

bool Treasure::getEdible() {
	return edible;
}
