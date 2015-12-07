#include "potion.h"
#include "player.h"
#include "item.h"
using namespace std;

Potion::Potion(int x, int y, Floor *f,::string potion_name) :Item(x, y, 'P', "Potion", f),P_name(potion_name) {};

string Potion::getPname() {
	return P_name;
}

