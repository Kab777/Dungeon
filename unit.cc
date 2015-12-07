#include <iostream>
#include "unit.h"
#include "floor.h"
using namespace std;


Unit::Unit() :X(0), Y(0), type(""), f(0) {};
Unit::Unit(int x, int y, char new_char, std::string new_type, Floor *new_f) :X(x), Y(y), ch(new_char), type(new_type), f(new_f) {};
Unit::~Unit() {
}

void Unit::notifyFloor() const {

}
void Unit::setType(string new_type) {
	type = new_type;
}
void Unit::setFloor(Floor * floor) {
	f = floor;
}
void Unit::setCoords(int x, int y) {
	X = x;
	Y = y;
}

int Unit::getX() {
	return X;
}

int Unit::getY() {
	return Y;
}

char Unit::getChar() {
	return ch;
}

string Unit::getType() {
	return type;
}

bool Unit::isValidPM(int x, int y) {
	return f->isValidPMove(x, y);
}

bool Unit::isValidEM(int x, int y) {
	return f->isValidEMove(x, y);
}

bool Unit::isTherePlayer(int x, int y){
	return f->isThereP(x, y);
}

void Unit::notifyChange(int x, int y, int oldX, int oldY, Unit *change, int PorE) {
	return f->notifyChange(x, y, oldX, oldY, change, PorE);
}
