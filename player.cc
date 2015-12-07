#include "player.h"
#include <iostream>
#include <climits>
#include <cstdlib>
using namespace std;

Player::Player(int x, int y, Floor *f, int hp, int def, int atk, std::string r_type)
	:Character(x, y, '@', "Player", f, hp, def, atk, r_type), gold(0) {
	action = "";
};

void Player::attack(std::string e_type) {};
int Player::getAttacked(int dmg, std::string e_type) {
	double ceiling = 100;
	double defense = getDef();
	double q = (ceiling / (ceiling + defense));
	int minus = q * dmg;
	int left_Hp = getHp() - minus;
	int miss = rand() % 2;
	if (miss == 0) {
		cout << e_type << " missed the attak" << endl;
		return -1;
	}
	if (e_type == "Elf") {
		if (getRace() != "Drow") {
			minus = 2 * minus;
			left_Hp = getHp() - minus;
		}
	}
	else if (e_type == "Orcs") {
		if (getRace() == "Goblin") {
			minus = 1.5 * minus;
			left_Hp = getHp() - minus;
		}
	}
	setHp(left_Hp);
	if (left_Hp == 0) {
		notifyChange(X,Y,X,Y, this, 0);
	}
	return minus;
}

int Player::getGold() {
	return gold;
}

void Player::changeGold(int amount) {
	int fn_gld = gold + amount;
	if (fn_gld < 0) {
		gold = 0;
	}
	else {
		gold = fn_gld;
	}
}
bool Player::move(string direction) {
	int fin_x;
	int fin_y;
	int flag = 0;
	if (direction == "no") {
		if (isValidPM(X - 1, Y)) {
			fin_x = X - 1;
			fin_y = Y;
			flag = 1;
		}
	}
	else if (direction == "so") {
		if (isValidPM(X+1, Y)) {
			fin_x = X+1;
			fin_y = Y;
			flag = 1;
		}
	}
	else if (direction == "ea") {
		if (isValidPM(X, Y+1)) {
			fin_x = X;
			fin_y = Y+1;
			flag = 1;
		}
	}
	else if (direction == "we") {
		if (isValidPM(X, Y-1)) {
			fin_x = X;
			fin_y = Y-1;
			flag = 1;
		}
	}
	else if (direction == "ne") {
		if (isValidPM(X - 1, Y+1)) {
			fin_x = X - 1;
			fin_y = Y+1;
			flag = 1;
		}
	}
	else if (direction == "nw") {
		if (isValidPM(X - 1, Y-1)) {
			fin_x = X - 1;
			fin_y = Y-1;
			flag = 1;
		}
	}
	else if (direction == "se") {
		if (isValidPM(X +1,Y+1)) {
			fin_x = X + 1;
			fin_y = Y + 1;
			flag = 1;
		}
	}
	else if (direction == "sw") {
		if (isValidPM(X + 1, Y-1)) {
			fin_x = X + 1;
			fin_y = Y -1;
			flag = 1;
		}
	}
	else {
		cout << "invalid dirction" << endl;
	}
	if (flag == 1) {
		oldX = X;
		oldY = Y;
		X = fin_x;
		Y = fin_y;
		action = "PC moves " + direction + ". ";
		notifyChange(fin_x, fin_y, oldX, oldY, this, 1);
		return true;
	}
	else {
		cout << "Invalid Movement, Please try again" << endl;
		return false;
	}
}

string Player::getAction() {
	return action;
}

void Player::setAction(string set) {
	action = set;
}
Player::~Player() {}

