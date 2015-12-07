#include "character.h"
#include <climits>

using namespace std;

Character::Character(int x, int y, char new_char, std::string new_type, Floor *new_f, int hp, int def, int atk, std::string new_race)
	:Unit(x, y, new_char, new_type, new_f), hp(hp), def(def), atk(atk),race(new_race) {
	if (new_race == "Vampire") {
		Max_Hp = INT_MAX;
	}
	else {
		Max_Hp = hp;
	}
};

int Character::getHp() {
	return hp;
}

int Character::getMaxHp() {
	return Max_Hp;
}

int Character::getDef() {
	return def;
}

int Character::getAtk() {
	return atk;
}

string Character::getRace() {
	return race;
}

void Character::setAtk(int set) {
	if (set < 0) {
		atk = 0;
	}
	else {
		atk = set;
	}
}

void Character::setDef(int set) {
	if (set < 0) {
		def = 0;
	}
	else {
		def = set;
	}
}

void Character::setHp(int set) {
	if (set < 0) {
		hp = 0;
	}
	else if (set > Max_Hp) {
		hp = Max_Hp;
	}
	else {
		hp = set;
	}
}
Character::~Character(){}

