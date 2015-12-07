#include "dragon.h"
#include "dragon_hoard.h"
using namespace std;

Dragon::Dragon(int x, int y, char c_type, Floor *f)
	:Enemy(x, y, c_type, f, 150, 20, 20, "Dragon", true) {};

Dragon::Dragon(int x, int y, char c_type, Floor *f, Dragon_Hoard *DH)
	:Enemy(x, y, c_type, f, 150, 20, 20, "Dragon", true), guard(DH) {};

void Dragon::Iamdead() {
	guard->changeEdible();
}
void Dragon::setGuard(Dragon_Hoard *dh) {
	guard = dh;
}
void Dragon::move() {
	detect();
	int fin_x = X;
	int fin_y = Y;
	if (isPlayer) {
		attack(getAtk(), getRace());
	}
	else {
		int T_X = guard->getX();
		int T_Y = guard->getY();
		if (X == (T_X - 1) && Y == (T_Y - 1)) { // nw
			if (isValidEM(X + 1, Y)) {
				fin_x = X + 1;
				fin_y = Y;
			}
			else if (isValidEM(X, Y+1)) {
				fin_x = X;
				fin_y = Y+1;
			}
		}
		else if (X == (T_X - 1) && Y == T_Y) { // no
			if (isValidEM(X, Y - 1)) {
				fin_x = X;
				fin_y = Y - 1;
			}
			else if (isValidEM(X, Y + 1)) {
				fin_x = X;
				fin_y = Y + 1;
			}
			else if (isValidEM(X + 1, Y - 1)) {
				fin_x = X + 1;
				fin_y = Y - 1;
			}
			else if (isValidEM(X + 1, Y + 1)) {
				fin_x = X + 1;
				fin_y = Y + 1;
			}
		}
		else if (X == (T_X - 1) && Y == (T_Y + 1)) { // ne
			if (isValidEM(X, Y - 1)) {
				fin_x = X;
				fin_y = Y - 1;
			}
			else if (isValidEM(X-1, Y)) {
				fin_x = X -1;
				fin_y = Y;
			}
		}
		else if (X == T_X && Y == (T_Y - 1)) { // w
			if (isValidEM(X -1, Y)) {
				fin_x = X -1;
				fin_y = Y;
			}
			else if (isValidEM(X -1, Y + 1)) {
				fin_x = X - 1;
				fin_y = Y + 1;
			}
			else if (isValidEM(X + 1, Y)) {
				fin_x = X + 1;
				fin_y = Y;
			}
			else if (isValidEM(X + 1, Y + 1)) {
				fin_x = X + 1;
				fin_y = Y + 1;
			}
		}
		else if (X == T_X && Y == (T_Y+1)) { // e
			if (isValidEM(X - 1, Y)) {
				fin_x = X - 1;
				fin_y = Y;
			}
			else if (isValidEM(X - 1, Y - 1)) {
				fin_x = X - 1;
				fin_y = Y - 1;
			}
			else if (isValidEM(X + 1, Y)) {
				fin_x = X + 1;
				fin_y = Y;
			}
			else if (isValidEM(X + 1, Y - 1)) {
				fin_x = X + 1;
				fin_y = Y - 1;
			}
		}
		else if (X == (T_X + 1) && Y == (T_Y - 1)) { // sw
			if (isValidEM(X - 1, Y)) {
				fin_x = X - 1;
				fin_y = Y;
			}
			else if (isValidEM(X, Y+1)) {
				fin_x = X;
				fin_y = Y + 1;
			}
		}
		else if (X == (T_X + 1) && Y == (T_Y + 1)) { // se
			if (isValidEM(X - 1, Y)) {
				fin_x = X - 1;
				fin_y = Y;
			}
			else if (isValidEM(X, Y - 1)) {
				fin_x = X;
				fin_y = Y - 1;
			}
		}
		else if (X == (T_X + 1) && Y == T_Y) { // so
			if (isValidEM(X, Y - 1)) {
				fin_x = X;
				fin_y = Y - 1;
			}
			else if (isValidEM(X, Y + 1)) {
				fin_x = X;
				fin_y = Y + 1;
			}
			else if (isValidEM(X - 1, Y - 1)) {
				fin_x = X - 1;
				fin_y = Y - 1;
			}
			else if (isValidEM(X - 1, Y + 1)) {
				fin_x = X - 1;
				fin_y = Y + 1;
			}
		}
		else {
			cerr << "Dragon in wrong position!! fix it!" << endl;
		}
	}
	if (fin_x == X && fin_y == Y) {//Dragon can't move, no need to modify anyting
		return;
	}
	else {
		oldX = X;
		oldY = Y;
		X = fin_x;
		Y = fin_y;
		notifyChange(fin_x, fin_y, oldX, oldY, this, 3);
	}
}

