#include "halfling.h"
#include <iostream>
using namespace std;

Halfling::Halfling(int x, int y, char c_type, Floor *f)
	:Enemy(x, y, c_type, f, 100, 20, 15, "Halfling", true) {};

int Halfling::getAttacked(int dmg, std::string race) {
	double ceiling = 100;
	double defense = getDef();
	double q = (ceiling / (ceiling + defense));
	int minus = q * dmg;
	int left_Hp = getHp() - minus;
	int flag = rand() % 2;
	if (flag == 0) {
		//cout << "you missed" << endl;
		return -1;
	}
	if (left_Hp < 0) {
		setHp(0);
	}
	else {
		setHp(left_Hp);
	}
	//cout << "Player deals" << minus << "damge" << endl;
	if (getHp() == 0) {
		//f->notifyChange(X, Y, X, Y, this, 2);
		cout << "enemy dies" << endl;
	}
	return minus;
}
