#include "dragon_hoard.h"
using namespace std;

Dragon_Hoard::Dragon_Hoard(int x, int y, Floor *f) :
	Treasure(x, y, f, "DH", 6, false) {
};

void Dragon_Hoard::addcord() {
	if (isValidEM(X - 1, Y - 1)) {
		ava_cord.push_back(make_pair(X-1, Y-1));
	}
	if (isValidEM(X - 1, Y)) {
		
		ava_cord.push_back(make_pair(X - 1, Y));
	}
	if (isValidEM(X - 1, Y + 1)) {
		
		ava_cord.push_back(make_pair(X-1, Y+1));
	}
	if (isValidEM(X, Y - 1)) {
		
		ava_cord.push_back(make_pair(X, Y-1));
	}
	if (isValidEM(X, Y + 1)) {
		
		ava_cord.push_back(make_pair(X, Y+1));
	}
	if (isValidEM(X + 1, Y - 1)) {
		
		ava_cord.push_back(make_pair(X+1, Y-1));
	}
	if (isValidEM(X + 1, Y)) {
		
		ava_cord.push_back(make_pair(X+1, Y));
	}
	if (isValidEM(X + 1, Y + 1)) {
		
		ava_cord.push_back(make_pair(X+1, Y+1));
	}
}
MyPair Dragon_Hoard::getRanCor() {
	addcord();
	int size = (int)ava_cord.size();
	return ava_cord[rand() % size];
}
Dragon_Hoard * Dragon_Hoard::getDH() {
	return this;
}

void Dragon_Hoard::UseOnPc() {
	int base = value;
	plyer->changeGold(base);
}

