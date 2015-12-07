#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <utility>


class Controller;
class Enemy;
class Potion;
class Treasure;
class Player;
class Unit;

typedef std::pair<int, int> MyPair;

class Floor {
	Unit *elements[1975]; // all elements in the floor
	Unit * temp_store;
	std::vector<std::pair<int, int> > *chamber[5]; // store 5 chambers in a floor, each chamber contains all belonged X and Y repreted as pairs
	std::vector<Enemy*> enemies; // store all enemies in a floor
	std::vector<Potion*> potions; // store all potions in a floor
	std::vector<Treasure*> treasures; // store all treatures in a floor
	std::string filename;
	int floor_num;
	int row;
	int column;
	char p_race;
	bool orimap;
	std::string fut_type;
	std::string cur_type;
	//void clearFloor(); // Frees all elements
	void generatePlayer(char);
	void generateStair();
	void generatePotion();
	void generate_One_Potion();
	void generateGold();
	void generate_One_Gold();
	void generateEnemy();
	void generate_One_Enemy();
	void generate_Dragon();
	void generate_One_Dragon(int cord);
	void setItemPc();
	void setDraH();
	MyPair getRandom();
	Controller *ctr;
	Player *pc;
public:
	void read_map();// read map from file name
	void nextFloor();
	void assign_chamber();
	void assign_cor(int ch_num, Unit *);
	Floor(std::string fname, Controller *, char pl_race = 's');
	~Floor();
	void notify(Unit *u); // notify controller
	bool isValidPMove(int, int);
	bool isValidEMove(int, int);
	bool isThereP(int, int);
	void notifyChange(int,int,int,int, Unit*, int); //move purpose, get signal from Unit
	void notifyPC(int hp, int atk, int def, int gold, std::string race, std::string quote ="");
	void changeMerchant();
	int getCol();
	int getRow();
	void moveP(std::string);
	void moveE();
	void usePotion(std::string);
	void Patk(std::string);
	void Eatk(int dmg, std::string e_type);
	void sortEnemyandTrea();
	bool isEnd();
	std::string getFut();
};
#endif


