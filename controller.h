#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include <sstream>
#include <string>
#include "textdisplay.h"

class Floor;
class Controller {
	TextDisplay *td;
	Floor *floor;
	std::string filename;
public:
	Controller(std::string filename);
	~Controller();
	void notify(int row, int column, char new_char);
	void notifyStats(int hp, int atk, int def, int gold, std::string race, std::string quote);
	void play();
	void notifyFloor(int);
};
#endif



