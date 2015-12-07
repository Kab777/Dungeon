#include "item.h"
#include "player.h"
using namespace std;



Item::Item(int x, int y, char new_char, std::string new_type, Floor *f) :Unit(x, y, new_char, new_type, f), plyer(NULL) {};

void Item::setPlayer(Player * my_player) {
	plyer = my_player;
}

