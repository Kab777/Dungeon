#include <fstream>
#include <sstream>
#include "controller.h"
#include "floor.h"
#include <locale>
#include <cstdlib>
using namespace std;



Controller::Controller(std::string new_filename) {
	if (new_filename == "Default.txt") {
		filename = new_filename;
	}
	else {
		string file = new_filename;
		ifstream ifs(file.c_str());
		for (int i = 1; i < 6; i++) {
			string s;
			stringstream ss;
			ss << i;
			string temp = "floor" + ss.str() + ".txt"; 
			ofstream ofs(temp.c_str());
			for (int j = 0; j < 25; j++) {
				getline(ifs, s);
				ofs << s << endl;
				if (j == 24) {
					ofs.close();
				}
			}
		}
		filename = "floor1.txt";
	}
}

void Controller::notifyStats(int hp, int atk, int def, int gold, std::string race, string quote) {
	td->notifyPlayer(hp, atk, def, gold, race, quote);
}
void Controller::play() {
	string race;
	cout << "If you want to change default character(Shade), press Y, otherwise press N" << endl;
	while (1) {
		cin >> race;
		if (race == "Y" || race == "y") {
			std::cout << "choose a character s/d/v/g/t" << std::endl;
			std::cin >> race;
			break;
		}
		else if (race == "N" || race == "n") {
			race = "s";
			break;
		}
		else {
			cout << "please press Y or N" << endl;
		}
	}
	while (1) {
		if (race == "s" || race == "d" || race == "v" || race == "g" || race == "t") {
			break;
		}
		else {
			cout << "invalid selection, retry" << endl;
		}
	}
	td = new TextDisplay(25, 79);
	std::locale loc;
	floor = new Floor(filename, this, tolower(race[0],loc));
	td->print();
	std::cout << "enter command " << std::endl;
	string cmd;
	cin >> cmd;
	while (1) {
		if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
			floor->moveP(cmd);
			//floor->moveE();
			td->print();
		}
		else if (cmd == "u") {
			cout << "which direction" << endl;
			cin >> cmd;
			if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
				floor->usePotion(cmd);
				floor->moveE();
				td->print();
			}
			else {
				std::cout << "invalid move " << std::endl;
			}
		}
		else if (cmd == "a") {
			cout << "enter enemy direction " << endl;
			cin >> cmd;
			if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
				floor->Patk(cmd);
				floor->moveE();
				td->print();
			}
			else {
				std::cout << "invalid attack " << std::endl;
			}
		}
		else if (cmd == "r") {
			delete floor;
			std::cout << "choose a character s/d/v/g/t" << std::endl;
			while (1) {
				cin >> race;
				if (race == "s" || race == "d" || race == "v" || race == "g" || race == "t") {
					break;
				}
				else {
					cout << "invalid selection, retry" << endl;
				}
			}
			floor = new Floor(filename, this, tolower(race[0], loc));
			td->print();
		}
		else if (cmd == "q") {
			cout << "game over" << endl;
			break;
		}
		else {
			std::cout << "invalid move " << std::endl;
		}
		if (floor->isEnd()) {
			cout << endl << endl;
			cout << "Your score is " << td->showG() << endl;
			cout << "Continue? Y/N" << endl;
			while (1){
				cin >> race;
				if (race == "Y" || race == "y") {
					cmd = "r";
					break;
				}
				else if (race == "N" || race == "n") {
					cmd = "q";
					break;
				}
				else {
					cout << "please press Y or N" << endl;
				}
			}
		}
		else {
			std::cout << "enter command " << std::endl;
			cin >> cmd;
		}
	}
}

void Controller::notify(int row, int column, char new_char) {
	td->notify(row, column, new_char);
}
void Controller::notifyFloor(int fnm) {
	td->notifyFloor(fnm);
}
Controller::~Controller() {
	for(int i=1; i<6; i++){
		ostringstream oss;
		oss << i;
		string s="floor"+oss.str()+".txt";
		remove(s.c_str());
	}
	delete td;
	delete floor;
}

