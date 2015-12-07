#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include "controller.h"
#include "floor.h"
#include "unit.h"
#include "player.h"
#include "Restore_Health.h"
#include "Boost_Atk.h"
#include "Boost_Def.h"
#include "Poison_Health.h"
#include "Wound_Atk.h"
#include "Wound_Def.h"
#include "Treasure.h"
#include "small_gold.h"
#include "normal_gold.h"
#include "dragon_hoard.h"
#include "merchant_hoard.h"
#include "enemy.h"
#include "halfling.h"
#include "human.h"
#include "dragon.h"
#include "dwarf.h"
#include "elf.h"
#include "orcs.h"
#include "merchant.h"
#include <assert.h>


using namespace std;

void Floor::notify(Unit *u) {
	ctr->notify(u->getX(), u->getY(), u->getChar());
}

int Floor::getCol() {
	return column;
}
int Floor::getRow() {
	return row;
}
void Floor::sortEnemyandTrea() {
	for (int i = 0; i < (int)enemies.size(); i++) {
		int mini = i;
		int y = enemies[i]->getX() * column + enemies[i]->getY();
		for (int j = i + 1; j < (int)enemies.size(); j++) {
			int x = enemies[j]->getX() * column + enemies[j]->getY();
			if (x < y) {
				mini = j;
			}
		}
		swap(enemies[i], enemies[mini]);
	}
	for (int i = 0; i < (int)treasures.size(); i++) {
		int mini = i;
		int y = treasures[i]->getX() * column + treasures[i]->getY();
		for (int j = i + 1; j < (int)treasures.size(); j++) {
			int x = treasures[j]->getX() * column + treasures[j]->getY();
			if (x < y) {
				mini = j;
			}
		}
		swap(treasures[i], treasures[mini]);
	}
}
string Floor::getFut() {
	return fut_type;
}
void Floor::moveP(std::string mvent) {
	if (pc->move(mvent)) {
		if (getFut() != "stair") {
			moveE();
		}
		if(pc->getRace() == "Troll"){
			pc->setHp(pc->getHp() + 5);
		}
	}
}
void Floor::moveE() {
	for (int i = 0; i < (int)enemies.size(); i++) {
		enemies[i]->move();
	}
	notifyPC(pc->getHp(), pc->getAtk(), pc->getDef(), pc->getGold(), pc->getRace(), pc->getAction());
}
Floor::~Floor() {
	for (int i = 0; i < 1975; i++) {
		delete elements[i];
	}
	for(int i=0; i<5;i++){
		delete chamber[i];
	}
}
bool Floor::isValidPMove(int x_cor, int y_cor) {
	return elements[x_cor*column + y_cor]->getType() == "tile" || elements[x_cor*column + y_cor]->getType() == "doorway"
		|| elements[x_cor*column + y_cor]->getType() == "passage" || elements[x_cor*column + y_cor]->getType() == "Treasure"
		|| elements[x_cor*column + y_cor]->getType() == "stair";
}
bool Floor::isValidEMove(int x_cor, int y_cor) {
	return elements[x_cor*column + y_cor]->getType() == "tile";
}


bool Floor::isThereP(int x_cor, int y_cor) {
	return elements[x_cor*column + y_cor]->getChar() == '@';
}

MyPair Floor::getRandom() {
	int cham_num = rand() % 5;
	int cham_size =(int)chamber[cham_num]->size();
	int my_row, my_col;
	while (1) {
		int pos = rand() % cham_size;
		my_row = chamber[cham_num]->at(pos).first;
		my_col = chamber[cham_num]->at(pos).second;
		if (elements[my_row * column + my_col]->getType() == "tile") return chamber[cham_num]->at(pos); // maybe full, fix later
	}

}

void Floor::setDraH() {
	for (int i = 0; i < static_cast<int>(treasures.size()); i++) {
		if (treasures[i]->getT_name() == "DH") {
			int x = treasures[i]->getX();
			int y = treasures[i]->getY();
			int d_x, d_y;
			if (elements[(x - 1)*column + (y - 1)]->getChar() == 'D') {
				d_x = x - 1;
				d_y = y - 1;
			}
			else if (elements[(x - 1)*column + y]->getChar() == 'D') {
				d_x = x - 1;
				d_y = y;
			}
			else if (elements[(x - 1)*column + y+1]->getChar() == 'D') {
				d_x = x - 1;
				d_y = y+1;
			}
			else if (elements[x*column + (y-1)]->getChar() == 'D') {
				d_x = x;
				d_y = y-1;
			}
			else if (elements[x*column + y+1]->getChar() == 'D') {
				d_x = x;
				d_y = y+1;
			}
			else if (elements[(x + 1)*column + y-1]->getChar() == 'D') {
				d_x = x + 1;
				d_y = y-1;
			}
			else if (elements[(x + 1)*column + y]->getChar() == 'D') {
				d_x = x + 1;
				d_y = y;
			}
			else if (elements[(x + 1)*column + y+1]->getChar() == 'D') {
				d_x = x + 1;
				d_y = y + 1;
			}
			else {
				cerr << "wrong map, can't find D near DH" << endl;
			}
			Dragon_Hoard *dh = dynamic_cast<Dragon_Hoard*>(treasures[i]);
			Dragon *dra = dynamic_cast<Dragon *>(elements[d_x*column + d_y]);
			dra->setGuard(dh->getDH());
		}
	}
}

void Floor::setItemPc() {
	for (int i = 0; i < (int)potions.size(); i++) {
		potions[i]->setPlayer(pc);
	}

	for (int i = 0; i < (int)treasures.size(); i++) {
		treasures[i]->setPlayer(pc);
	}
}
Floor::Floor(std::string fname, Controller *ct, char race):row(25), column(79), cur_type("tile"), fut_type("tile"),floor_num(1),p_race(race), orimap(true) {
	filename = fname;
	ctr = ct;
	temp_store = NULL;
	read_map();
	assign_chamber();
	if (orimap) {
		generatePlayer(race);
		generateStair();
		generatePotion();
		generateGold();
		generateEnemy();
	}
	else {
		setDraH();
	}
	sortEnemyandTrea();
	setItemPc();
	ctr->notifyFloor(1);
}

void Floor::assign_chamber() {
	for (int i = 0; i < 5; i++) {
		chamber[i] = new vector<pair<int, int> >;
	}
	for (int i = 3; i < 7; i++) {
		for (int j = 3; j < 29; j++) {
			assign_cor(0, elements[i*column+j]); // top_left chamber; 0
		}
	}

	for (int i = 15; i < 22; i++) {
		for (int j = 4; j < 25; j++) {
			assign_cor(1, elements[i*column+j]); // bot_left chamber; 1
		}
	}

	for (int i = 10; i < 13; i++) {
		for (int j = 38; j < 50; j++) {
			assign_cor(2, elements[i*column+j]); // mid chamber; 2
		}
	}

	for (int i = 3; i < 14; i++) { // top right chamber; 3
		for (int j = 39; j < 76; j++) {
			if (i < 5) {
				if (j < 62) {
					assign_cor(3, elements[i*column+j]);
				}
			}
			else if (i == 5) {
				if (j < 70) {
					assign_cor(3, elements[i*column+j]);
				}
			}
			else if (i == 6) {
				if (j < 73) {
					assign_cor(3, elements[i*column+j]);
				}
			}
			else {
				if (j > 60) {
					assign_cor(3, elements[i*column+j]);
				}
			}
		}
	}

	for (int i = 16; i < 22; i++) {// bot right chamber; 3
		for (int j = 37; j < 76; j++) {
			if (i < 19) {
				if (j > 64) {
					assign_cor(4, elements[i*column+j]);
				}
			}
			else {
				assign_cor(4, elements[i*column+j]);
			}
		}
	}
}

void Floor::assign_cor(int ch_num, Unit *new_unit) {
	int i = new_unit->getX();
	int j= new_unit->getY();
	chamber[ch_num]->push_back(make_pair(i, j));
}
bool Floor::isEnd() {
	if (pc->getHp() == 0 || floor_num == 6) {
		return true;
	}
	else {
		return false;
	}
}
void Floor::notifyChange(int x, int y, int oldX, int oldY, Unit *change, int status) {// 0 player&dead, 1 player&live, 3 enemy&live
	int cord = x*column + y;
	int old_cord = oldX*column + oldY;
	string temp = elements[cord]->getType();
	if (temp == "stair") {
		nextFloor();
		return;
		//new floor
	}
	if (status == 0) {
		bool isWin();
		//delete all
		return;
	}
	if (status == 1) {//live player calling notifychange
		fut_type = temp;
		if (fut_type == "Treasure") {// next move is treature
			Treasure *tp = dynamic_cast<Treasure*>(elements[cord]);
			if (tp->getEdible()) {
				tp->UseOnPc();
				pc->setAction(pc->getAction() + "PC eats " + tp->getT_name() + ". ");
				for (int i = 0; i < (int)treasures.size(); i++) {
					if (treasures[i]->getX() == tp->getX() && treasures[i]->getY() == tp->getY()) {
						treasures.erase(treasures.begin() + i);
						break;
					}
				}
			}
			else {//dragon protected dragon hoard
				temp_store = elements[cord];
				if (cur_type == "tile") {
					elements[old_cord] = new Unit(oldX, oldY, '.', "tile", this);
				}
				else if (cur_type == "passage") {
					elements[old_cord] = new Unit(oldX, oldY, '#', "passage", this);
				}
				else if (cur_type == "doorway") {
					elements[old_cord] = new Unit(oldX, oldY, '+', "doorway", this);
				}
				else if (cur_type == "Treasure") {
					if (temp_store != NULL) {
						elements[old_cord] = temp_store;
						temp_store = NULL;
					}
					else {
						elements[old_cord] = new Unit(oldX, oldY, '.', "tile", this);
					}
				}
				else {
					cerr << "notifychange wrong, not valid move" << endl;
				}
				elements[cord] = change;
				cur_type = fut_type;
				notify(change);
				notify(elements[old_cord]);
				notifyPC(pc->getHp(), pc->getAtk(), pc->getDef(), pc->getGold(), pc->getRace());
				return;
			}
			cur_type = fut_type;
			notifyPC(pc->getHp(), pc->getAtk(), pc->getDef(), pc->getGold(), pc->getRace());
		}
		// future is not treasure
		if (cur_type == "tile") {
			elements[old_cord] = new Unit(oldX, oldY, '.', "tile", this);
		}
		else if (cur_type == "passage") {
			elements[old_cord] = new Unit(oldX, oldY, '#', "passage", this);
		}
		else if (cur_type == "doorway") {
			elements[old_cord] = new Unit(oldX, oldY, '+', "doorway", this);
		}
		else if (cur_type == "Treasure") {
			if (temp_store != NULL) {
				elements[old_cord] = temp_store;
				temp_store = NULL;
			}
			else {
				elements[old_cord] = new Unit(oldX, oldY, '.', "tile", this);
			}
		}
		else {
			cerr << "notifychange wrong, not valid move" << endl;
		}
		cur_type = fut_type;
	}
	else {//enemy
		elements[old_cord] = new Unit(oldX, oldY, '.', "tile", this);
	}
	delete elements[cord];
	elements[cord] = change;
	notify(change);
	notify(elements[old_cord]);
}
void Floor::notifyPC(int hp, int atk, int def, int gold, std::string race, string quote) {
	ctr->notifyStats(hp, atk, def, gold, race, quote);
}
void Floor::generatePlayer(char player_type) {
	MyPair pos = getRandom();
	int i = pos.first;
	int j = pos.second;
	int hp;
	int def;
	int atk;
	string race;
	int cord = i*column + j;
	delete elements[cord];
	switch (player_type) {
	case ('s') : {
		hp = 125;
		atk = 25;
		def = 25;
		race = "Shade";
		pc = new Shade(i, j, this, hp, def, atk);
		elements[cord] = pc;
		break;
	}
	case ('d') : {
		hp = 150;
		atk = 25;
		def = 15;
		race = "Drow";
		pc = new Drow(i, j, this, hp, def, atk);
		elements[cord] = pc;
		break;
	}
	case ('v') : {
		hp = 50;
		atk = 25;
		def = 25;
		race = "Vampire";
		pc = new Vampire(i, j, this, hp, def, atk);
		elements[cord] = pc;
		break;
	}
	case ('g') : {
		hp = 110;
		atk = 15;
		def = 20;
		race = "Goblin";
		pc = new Goblin(i, j, this, hp, def, atk);
		elements[cord] = pc;
		break;
	}
	case ('t') : {
		hp = 120;
		atk = 25;
		def = 15;
		race = "Troll";
		pc = new Troll(i, j, this, hp, def, atk);
		elements[cord] = pc;
		break;
	}
	default:
		std::cerr << "invalid selection" << std::endl;
	}

	notifyPC(hp, atk, def, 0, race,"Player character has spawned.");
	notify(elements[cord]);

}
void Floor::generateStair() {
	MyPair pos = getRandom();
	int i = pos.first;
	int j = pos.second;
	int cord = i*column + j;
	delete elements[cord];
	elements[cord] = new Unit(i, j, '\\', "stair", this);
	notify(elements[cord]);
}
void Floor::generatePotion() {
	for (int i = 0; i < 10; i++) {
		generate_One_Potion();
	}
}
void Floor::generate_One_Potion() {// do I need to store all potions into a vector?
	MyPair pos = getRandom();
	int i = pos.first;
	int j = pos.second;
	int cord = i*column + j;
	delete elements[cord];
	int potion_type = rand() % 6;
	switch (potion_type) {
	case(0) : {
		Restore_Health *temp = new Restore_Health(i, j, this);
		potions.push_back(temp);
		elements[cord] = temp;
		break;
		}
	case(1) :{
		Boost_Atk *temp = new Boost_Atk(i, j, this);
		potions.push_back(temp);
		elements[cord] = temp;
		break;
		}
	case(2) :{
		Boost_Def *temp = new Boost_Def(i, j, this);
		potions.push_back(temp);
		elements[cord] = temp;
		break;
		}
	case(3) :{
		Poison_Health *temp = new Poison_Health(i, j, this);
		potions.push_back(temp);
		elements[cord] = temp;
		break;
		}
	case(4) : {
		Wound_Atk *temp = new Wound_Atk(i, j, this);
		potions.push_back(temp);
		elements[cord] = temp;
		break;
		}
	case(5) : {
		Wound_Def *temp = new Wound_Def(i, j, this);
		potions.push_back(temp);
		elements[cord] = temp;
		break;
		}
	}
	notify(elements[cord]);
}
void Floor::generateGold() {
	for (int i = 0; i < 10; i++) {
		generate_One_Gold();
	}
}
void Floor::generate_One_Gold() {
	MyPair pos = getRandom();
	int i = pos.first;
	int j = pos.second;
	int cord = i*column + j;
	int gold_type = rand() % 8;
	if (gold_type < 2) { //1/4 small gold
		delete elements[cord];
		Small_Gold *new_SG = new Small_Gold(i, j, this);
		elements[cord] = new_SG;
		treasures.push_back(new_SG);
	}
	else if (gold_type == 2) {// 1/8 dragon hoard
		while (1) {
			if (isValidEMove(i - 1, j - 1) || isValidEMove(i - 1, j) || isValidEMove(i - 1, j + 1) || isValidEMove(i, j - 1) || isValidEMove(i, j + 1)
				|| isValidEMove(i + 1, j - 1) || isValidEMove(i + 1, j) || isValidEMove(i + 1, j + 1)) {
				delete elements[cord];
				Dragon_Hoard *new_DH = new Dragon_Hoard(i, j, this);
				elements[cord] = new_DH;
				treasures.push_back(new_DH);
				break;
			}
			else {
				pos = getRandom();
				i = pos.first;
				j = pos.second;
				cord = i*column + j;
			}
		}

	}
	else {
		delete elements[cord];
		Normal_Gold *new_NG = new Normal_Gold(i, j, this);
		elements[cord] = new_NG;
		treasures.push_back(new_NG);
	}
	notify(elements[cord]);
}
void Floor::generateEnemy() {
	for (int i = 0; i < 20; i++) {
		generate_One_Enemy();
	}
	generate_Dragon();
}
void Floor::generate_One_Enemy() { // add a sort enemy later
	MyPair pos = getRandom();
	int i = pos.first;
	int j = pos.second;
	int cord = i*column + j;
	delete elements[cord];
	int enm_type = rand() % 18;
	if (enm_type < 4) { //
		Human *new_hum = new Human(i, j, 'H', this);
		elements[cord] = new_hum;
		enemies.push_back(new_hum);
	}
	else if (enm_type < 7) {
		Dwarf *new_Dwf = new Dwarf(i, j, 'W', this);
		elements[cord] = new_Dwf;
		enemies.push_back(new_Dwf);
	}
	else if (enm_type < 9) {
		Elf *new_elf = new Elf(i, j, 'E', this);
		elements[cord] = new_elf;
		enemies.push_back(new_elf);
	}
	else if (enm_type < 11) {
		Orcs *new_orcs = new Orcs(i, j, 'O', this);
		elements[cord] = new_orcs;
		enemies.push_back(new_orcs);
	}
	else if (enm_type < 13) {
		Merchant *new_mer = new Merchant(i, j, 'M', this);
		elements[cord] = new_mer;
		enemies.push_back(new_mer);
	}
	else {
		Halfling *new_hal = new Halfling(i, j, 'L', this);
		elements[cord] = new_hal;
		enemies.push_back(new_hal);
	}
	notify(elements[cord]);
}
void Floor::generate_Dragon() {
	for (int i = 0; i < static_cast<int>(treasures.size()); i++) {
		if (treasures[i]->getT_name() == "DH") {
			generate_One_Dragon(treasures[i]->getX()*column + treasures[i]->getY());
		}
	}
}
void Floor::generate_One_Dragon(int trea_cord) {
	if (dynamic_cast<Dragon_Hoard*>(elements[trea_cord])) {
		Dragon_Hoard *temp = dynamic_cast<Dragon_Hoard*>(elements[trea_cord]);
		MyPair new_pair = temp->getRanCor();
		int i = new_pair.first;
		int j = new_pair.second;
		delete elements[i*column + j];
		Dragon *new_dra = new Dragon(i, j, 'D', this, temp->getDH());
		elements[i*column + j] = new_dra;
		enemies.push_back(new_dra);
		notify(elements[i*column + j]);
	}
	else {
		cout << "generate one dragon is wrong " << endl;
	}
}
void Floor::read_map() {
	string line;
	string new_type;
	ifstream ifs(filename.c_str());
	for (int i = 0; i < 1975; i++) {
		elements[i] = new Unit;
	}
	for (int i = 0; i < row; ++i) {
		getline(ifs, line);
		for (int j = 0; j < column; j++) {
			int cord = i*column + j;
			char c_type = line[j];
			delete elements[cord];
			if (c_type == ' ' || c_type == '\t') {
				elements[cord] = new Unit(i, j, c_type, "empty", this);
			}
			else if (c_type == '.') {
				elements[cord] = new Unit(i, j, c_type, "tile", this);
			}
			else if (c_type == '|' || c_type == '-') {
				elements[cord] = new Unit(i, j, c_type, "wall", this);
			}
			else if (c_type == '+') {
				elements[cord] = new Unit(i, j, c_type, "doorway", this);
			}
			else if (c_type == '#') {
				elements[cord] = new Unit(i, j, c_type, "passage", this);
			}
			else if (c_type == '\\') {
				elements[cord] = new Unit(i, j, c_type, "stair", this);
			}
			else if (c_type == 'H') {
				Human *new_hum = new Human(i, j, c_type, this);
				elements[cord] = new_hum;
				enemies.push_back(new_hum);
			}
			else if (c_type == 'W') {
				Dwarf *new_Dwf = new Dwarf(i, j, c_type, this);
				elements[cord] = new_Dwf;
				enemies.push_back(new_Dwf);
			}
			else if (c_type == 'E') {
				Elf *new_elf = new Elf(i, j, c_type, this);
				elements[cord] = new_elf;
				enemies.push_back(new_elf);
			}
			else if (c_type == 'O') {
				Orcs *new_orcs = new Orcs(i, j, c_type, this);
				elements[cord] = new_orcs;
				enemies.push_back(new_orcs);
			}
			else if (c_type == 'M') {
				Merchant *new_mer = new Merchant(i, j, c_type, this);
				elements[cord] = new_mer;
				enemies.push_back(new_mer);
			}
			else if (c_type == 'D') {
				Dragon *new_dra = new Dragon(i, j, c_type, this);
				elements[cord] = new_dra;
				enemies.push_back(new_dra);
			}
			else if (c_type == 'L') {
				Halfling *new_hal = new Halfling(i, j, c_type, this);
				elements[cord] = new_hal;
				enemies.push_back(new_hal);
			}
			else if (c_type == '0') {
				Restore_Health *new_RH = new Restore_Health(i, j, this);
				elements[cord] = new_RH;
				potions.push_back(new_RH);
			}
			else if (c_type == '1') {
				Boost_Atk *new_BA = new Boost_Atk(i, j, this);
				elements[cord] = new_BA;
				potions.push_back(new_BA);
			}
			else if (c_type == '2') {
				Boost_Def *new_BD = new Boost_Def(i, j, this);
				elements[cord] = new_BD;
				potions.push_back(new_BD);
			}
			else if (c_type == '3') {
				Poison_Health *new_PH = new Poison_Health(i, j, this);
				elements[cord] = new_PH;
				potions.push_back(new_PH);
			}
			else if (c_type == '4') {
				Wound_Atk *new_WA = new Wound_Atk(i, j, this);
				elements[cord] = new_WA;
				potions.push_back(new_WA);
			}
			else if (c_type == '5') {
				Wound_Def *new_WD = new Wound_Def(i, j, this);
				elements[cord] = new_WD;
				potions.push_back(new_WD);
			}
			else if (c_type == '6') {
				Normal_Gold *new_NG = new Normal_Gold(i, j, this);
				elements[cord] = new_NG;
				treasures.push_back(new_NG);
			}
			else if (c_type == '7') {
				Small_Gold *new_SG = new Small_Gold(i, j, this);
				elements[cord] = new_SG;
				treasures.push_back(new_SG);
			}
			else if (c_type == '8') {
				Merchant_Hoard *new_MH = new Merchant_Hoard(i, j, this);
				elements[cord] = new_MH;
				treasures.push_back(new_MH);
			}
			else if (c_type == '9') {
				Dragon_Hoard *new_DH = new Dragon_Hoard(i, j, this);
				elements[cord] = new_DH;
				treasures.push_back(new_DH);
			}
			else if (c_type == '@') {
				orimap = false;
				int hp, atk, def;
				string race;
				switch (p_race) {
				case ('s') : {
					hp = 125;
					atk = 25;
					def = 25;
					pc = new Shade(i, j, this, hp, def, atk);
					elements[cord] = pc;
					race = "Shade";
					break;
				}
				case ('d') : {
					hp = 150;
					atk = 25;
					def = 15;
					pc = new Drow(i, j, this, hp, def, atk);
					elements[cord] = pc;
					race = "Drow";
					break;
				}
				case ('v') : {
					hp = 50;
					atk = 25;
					def = 25;
					pc = new Vampire(i, j, this, hp, def, atk);
					elements[cord] = pc;
					race = "Vampire";
					break;
				}
				case ('g') : {
					hp = 110;
					atk = 15;
					def = 20;
					pc = new Goblin(i, j, this, hp, def, atk);
					elements[cord] = pc;
					race = "Goblin";
					break;
				}
				case ('t') : {
					hp = 120;
					atk = 25;
					def = 15;
					pc = new Troll(i, j, this, hp, def, atk);
					elements[cord] = pc;
					race = "Troll";
					break;
				}
				default:
					std::cout << "invalid selection" << std::endl;
				}
				elements[cord] = pc;
				notifyPC(hp, atk, def, 0, race, "Player character has spawned.");
			}
			else {
				cout << c_type << endl;
				cout << "wrong map" << endl;
			}
			notify(elements[cord]);
		}
	}
}
void Floor::nextFloor() {
	if (floor_num == 5) {
		floor_num++;
		return;
	}
	int ini_hp = pc->getHp();
	int ini_gold = pc->getGold();
	for (int i = 0; i < 1975; i++) {
		delete elements[i];
	}
	floor_num++;
	ctr->notifyFloor(floor_num);
	enemies.clear();
	potions.clear();
	treasures.clear();
	if (!orimap) {
		stringstream ss;
		ss << floor_num;
		filename = "floor" + ss.str() + ".txt";
		read_map();
		pc->setHp(ini_hp);
		pc->changeGold(ini_gold);
		cur_type = "tile";
		fut_type = "tile";
		setDraH();
		sortEnemyandTrea();
	}
	else {//orig map
		read_map();
		generatePlayer(p_race);
		pc->setHp(ini_hp);
		pc->changeGold(ini_gold);
		generateStair();
		generatePotion();
		generateGold();
		generateEnemy();
		sortEnemyandTrea();
		cur_type = "tile";
		fut_type = "tile";
	}
	setItemPc();
}
void Floor::usePotion(std::string direction) {
	int x_cor, y_cor, pos;
	if (direction == "no") {
		x_cor = pc->getX() - 1;
		y_cor = pc->getY();
	}
	else if (direction == "so") {
		x_cor = pc->getX() + 1;
		y_cor = pc->getY();
	}
	else if (direction == "ea") {
		x_cor = pc->getX();
		y_cor = pc->getY()+1;
	}
	else if (direction == "we") {
		x_cor = pc->getX();
		y_cor = pc->getY()-1;
	}
	else if (direction == "ne") {
		x_cor = pc->getX() - 1;
		y_cor = pc->getY() + 1;
	}
	else if (direction == "nw") {
		x_cor = pc->getX() - 1;
		y_cor = pc->getY() - 1;
	}
	else if (direction == "se") {
		x_cor = pc->getX() + 1;
		y_cor = pc->getY() + 1;
	}
	else if (direction == "sw") {
		x_cor = pc->getX() + 1;
		y_cor = pc->getY() - 1;
	}
	else {
		cout << "invalid dirction" << endl;
		return;
	}
	pos = x_cor * column + y_cor;
	if (elements[pos]->getType() == "Potion") {
		Potion *pt = dynamic_cast<Potion*>(elements[pos]);
		pt->UseOnPC();
		pc->setAction("PC uses " + pt->getPname() + ".");
		for (int i = 0; i < (int)potions.size(); i++) {
			if (potions[i]->getX() == pt->getX() && potions[i]->getY() == pt->getY()) {
				potions.erase(potions.begin() + i);
				break;
			}
		}
		delete elements[pos];
		elements[pos] = new Unit(x_cor, y_cor, '.', "tile", this);
		notify(elements[pos]);
		//notifyPC(pc->getHp(), pc->getAtk(), pc->getDef(), pc->getGold(), pc->getRace(), pc->getAction());
	}
	else {
		cout << "there is no potion there" << endl;
	}
}
void Floor::changeMerchant() {
	for (int i = 0; i < static_cast<int>(enemies.size()); i++) {
		if (enemies[i]->getRace() == "Merchant") {
			enemies[i]->changeHostility();
		}
	}
}
void Floor::Patk(string direction) {
	int x_cor, y_cor, pos;
	if (direction == "no") {
		x_cor = pc->getX() - 1;
		y_cor = pc->getY();
	}
	else if (direction == "so") {
		x_cor = pc->getX() + 1;
		y_cor = pc->getY();
	}
	else if (direction == "ea") {
		x_cor = pc->getX();
		y_cor = pc->getY() + 1;
	}
	else if (direction == "we") {
		x_cor = pc->getX();
		y_cor = pc->getY() - 1;
	}
	else if (direction == "ne") {
		x_cor = pc->getX() - 1;
		y_cor = pc->getY() + 1;
	}
	else if (direction == "nw") {
		x_cor = pc->getX() - 1;
		y_cor = pc->getY() - 1;
	}
	else if (direction == "se") {
		x_cor = pc->getX() + 1;
		y_cor = pc->getY() + 1;
	}
	else if (direction == "sw") {
		x_cor = pc->getX() + 1;
		y_cor = pc->getY() - 1;
	}
	else {
		cout << "invalid dirction" << endl;
		return;
	}
	pos = x_cor * column + y_cor;
	if (elements[pos]->getType() == "Enemy") {
		string act = "";
		pc->setAction(act);
		int success;
		Enemy *pt = dynamic_cast<Enemy*>(elements[pos]);
		success = pt->getAttacked(pc->getAtk(), pc->getRace());// attck happens here
		if (success != -1) {// enemey gets attack, vampire needs to to update
			stringstream ss;
			ss << success;
			act = pc->getAction() + "PC deals" + ss.str() + "damage to " + pt->getRace() + "(";
			pc->attack(pt->getType());//gain hp, steal gold ...
			ss.str("");
			ss.clear();
			ss << pt->getHp();
			act = act + ss.str() + "HP)";
			pc->setAction(act);
		}
		else {
			pc->setAction(pc->getAction() + "PC missed attack. ");
		}
		if (pt->getHp() == 0) {
			for (int i = 0; i < (int)enemies.size(); i++) {
				if (enemies[i]->getX() == pt->getX() && enemies[i]->getY() == pt->getY()) {
					enemies.erase(enemies.begin() + i);
					break;
				}
			}
			if (pt->getRace() == "Dragon") {
				Dragon *temp = dynamic_cast<Dragon*>(elements[pos]);
				temp->Iamdead();
				delete elements[pos];
				elements[pos] = new Unit(x_cor, y_cor, '.', "tile", this);
			}
			else if (pt->getRace() == "Human") {
				delete elements[pos];
				Normal_Gold *new_NG = new Normal_Gold(x_cor, y_cor, this);
				new_NG->setPlayer(pc);
				elements[pos] = new_NG;
				treasures.push_back(new_NG);
			}
			else if (pt->getRace() == "Merchant") {
				delete elements[pos];
				Merchant_Hoard *new_MH = new Merchant_Hoard(x_cor, y_cor, this);
				new_MH->setPlayer(pc);
				elements[pos] = new_MH;
				treasures.push_back(new_MH);
			}
			else {
				delete elements[pos];
				elements[pos] = new Unit(x_cor, y_cor, '.', "tile", this);
			}
			
		}
		notify(elements[pos]);
		notifyPC(pc->getHp(), pc->getAtk(), pc->getDef(), pc->getGold(), pc->getRace());
	}
	else {
		cout << "not attacking an enemy" << endl;
	}
}

void Floor::Eatk(int dmg, std::string e_type) {
	int e_damg = pc->getAttacked(dmg, e_type);
	stringstream ss;
	ss << e_damg;
	if (e_damg == -1) {// missed
		pc->setAction(pc->getAction() + e_type + " missed the attack");
	}
	else {
		pc->setAction(pc->getAction() + e_type + " deals " + ss.str() + "damage to PC. ");
	}
	notifyPC(pc->getHp(), pc->getAtk(), pc->getDef(), pc->getGold(), pc->getRace());
}

