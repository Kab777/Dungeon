#ifndef UNIT_H
#define UNIT_H
#include <string>
#include "floor.h"
//class Floor;
class Unit {
protected:
	int X;
	int Y;
	char ch;
	std::string type;
	Floor *f;
	void notifyFloor() const; // notify floor, floor will then notify textdisplay
public:
	Unit();
	Unit(int x, int y, char new_char, std::string new_type, Floor *new_f);
	int getX();
	int getY();
	char getChar();
	std::string getType();
	void setCoords(int x, int y);
	void setFloor(Floor * floor);
	void setType(std::string type);
	void notifyChange(int x, int y, int, int, Unit*, int);
	bool isValidPM(int, int);
	bool isValidEM(int, int);
	bool isTherePlayer(int, int);
	virtual ~Unit();
};
#endif






