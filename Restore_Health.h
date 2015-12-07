#ifndef RESTORE_HEALTH
#define RESTORE_HEALTH
#include "potion.h"
class Restore_Health :public Potion{
public:
	Restore_Health(int x, int y, Floor *f);
	void UseOnPC();
};
#endif

