#include "textdisplay.h"
#include <iomanip>
#include <string>
using namespace std;


TextDisplay::TextDisplay(int new_row, int new_col):row(new_row),col(new_col),Hp(0), Atk(0), Def(0), Gold(0), floor_num(1),action(""){
	Display = new char *[row];
	for (int i = 0; i < row; i++) {
		Display[i] = new char[col];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Display[i][j] = ' ';
		}
	}
}

void TextDisplay::notifyFloor(int fnum) {
	floor_num = fnum;
}
void TextDisplay::notifyPlayer(int hp, int atk, int def, int gold, std::string race, std::string quote) {
	Hp = hp;
	Atk = atk;
	Def = def;
	Gold = gold;
	Race = race;
	action += quote;
}
TextDisplay::~TextDisplay() {
	for (int i = 0; i < row; i++) {
		delete[] Display[i];
	}
	delete[] Display;
}

void TextDisplay::notify(int my_row, int my_col, char my_ch) {
	if (my_row < row && my_row >= 0 && my_col < col && my_col >= 0) {
		Display[my_row][my_col] = my_ch;
		//cout << "row :" << my_row << " col is " << my_col << " char is " << my_ch << endl;
	}
	else {
		cerr << "invalid notify in Textdislay" << endl;
	}
}

void TextDisplay::print() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << Display[i][j];
		}
		cout << endl;
	}
	cout << "Race: " << left << setw(7) << Race
		<< " Gold: " << left << setw(3) << Gold
		<< right << setw(col - 27) << "Floor " << floor_num << endl
		<< "HP: " << Hp << endl
		<< "Atk: " << Atk << endl
		<< "Def: " << Def << endl
		<< "Action: " << action << endl;
	action = "";
}

int TextDisplay::showG() {
	return Gold;
}

