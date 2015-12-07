#include "merchant.h"

using namespace std;

Merchant::Merchant(int x, int y, char c_type, Floor *f)
	:Enemy(x, y, c_type, f, 30, 5, 70, "Merchant", false) {};

int Merchant::getAttacked(int dmg, std::string race) {
	f->changeMerchant();
	double ceiling = 100;
	double defense = getDef();
	double q = (ceiling / (ceiling + defense));
	int minus = q * dmg;
	int left_Hp = getHp() - minus;
	setHp(left_Hp);
	return minus;
}
