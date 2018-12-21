#pragma once
#include "Magic.h"

class Heal : public Magic {
private:
	int type;
	int damage;
	int attackable;//“¯S‰~‚Ì”ÍˆÍA-1‚Ì‚Í‘S”ÍˆÍ
	int attack_area;//UŒ‚”ÍˆÍ
	virtual void effectpoint(int, Player**, int, Enemy**, int);
public:
	Heal();
	virtual bool effectBattle(stagedata, Player**, int, int, Enemy**, int);
	virtual void effectMap();
};