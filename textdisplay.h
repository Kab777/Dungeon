#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>

class TextDisplay {
	char **Display;
	int row, col;
	int Hp, Atk, Def, Gold;
	int floor_num;
	std::string Race;
	std::string action;
	//std::string Eaction;
public:
	TextDisplay(int row, int col);
	void notify(int row, int col, char ch); //gets notified by entities of state change
	void notifyPlayer(int hp, int atk, int def, int gold, std::string race, std::string quote);
	void print();
	void notifyFloor(int);
	int showG();
	~TextDisplay();
};
#endif

