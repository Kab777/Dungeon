#include "enemy.h"
#include <iostream>
#include "player.h"
using namespace std;

Enemy::Enemy(int x, int y, char c_type, Floor *f, int hp, int def, int atk, string r_type, bool is_hostile)
	:Character(x, y, c_type, "Enemy", f, hp, def, atk, r_type), hostile(is_hostile) {
	detect();
};
Enemy::~Enemy() {}

void Enemy::move() {
	int ran_num;
	int fin_x;
	int fin_y;
	detect();
	if (isPlayer && hostile) {
		attack(getAtk(), getRace());
	}
	else {
		while (1) {
			ran_num = rand() % 8;
			if (ran_num == 0) {
				if (isValidEM(X - 1, Y)) {
					fin_x = X - 1;
					fin_y = Y;
					break;
				}
			}
			else if (ran_num == 1) {
				if (isValidEM(X + 1, Y)) {
					fin_x = X + 1;
					fin_y = Y;
					break;
				}
			}
			else if (ran_num == 2) {
				if (isValidEM(X, Y + 1)) {
					fin_x = X;
					fin_y = Y + 1;
					break;
				}
			}
			else if (ran_num == 3) {
				if (isValidEM(X, Y - 1)) {
					fin_x = X;
					fin_y = Y - 1;
					break;
				}
			}
			else if (ran_num == 4) {
				if (isValidEM(X - 1, Y + 1)) {
					fin_x = X - 1;
					fin_y = Y + 1;
					break;
				}
			}
			else if (ran_num == 5) {
				if (isValidEM(X - 1, Y - 1)) {
					fin_x = X - 1;
					fin_y = Y - 1;
					break;
				}
			}
			else if (ran_num == 6) {
				if (isValidEM(X + 1, Y + 1)) {
					fin_x = X + 1;
					fin_y = Y + 1;
					break;
				}
			}
			else {
				if (isValidEM(X + 1, Y - 1)) {
					fin_x = X + 1;
					fin_y = Y - 1;
					break;
				}
			}
		}
		oldX = X;
		oldY = Y;
		X = fin_x;
		Y = fin_y;
		notifyChange(fin_x, fin_y, oldX, oldY, this, 3);
	}
}
int Enemy::getAttacked(int dmg, std::string race) {
	double ceiling = 100;
	double defense = getDef();
	double q = (ceiling / (ceiling + defense));
	int minus = q * dmg;
	int left_Hp = getHp() - minus;
	setHp(left_Hp);
	//cout << "Player deals" << minus << "damage" << endl;
	if (getHp() == 0) {
		cout << "enemy dies" << endl;
	}
	return minus;
}
void Enemy::attack(int dmg, std::string e_type) {
	if (isPlayer && hostile) {
		f->Eatk(dmg,e_type);
	}
}
void Enemy::detect() {
	if (isTherePlayer(X - 1, Y - 1)) {
		isPlayer = true;
	}
	else if (isTherePlayer(X - 1, Y)) {
		isPlayer = true;
	}
	else if (isTherePlayer(X - 1, Y + 1)) {
		isPlayer = true;
	}
	else if (isTherePlayer(X, Y - 1)) {
		isPlayer = true;
	}
	else if (isTherePlayer(X, Y + 1)) {
		isPlayer = true;
	}
	else if (isTherePlayer(X + 1, Y - 1)) {
		isPlayer = true;
	}
	else if (isTherePlayer(X + 1, Y)) {
		isPlayer = true;
	}
	else if (isTherePlayer(X + 1, Y + 1)) {
		isPlayer = true;
	}
	else {
		isPlayer = false;
	}
}

void Enemy::changeHostility() {
		hostile = true;
}
