#pragma once
#include "Magic.h"

class Heal : public Magic {
private:
	int type;
	int point;
	int attackable;//“¯S‰~‚Ì”ÍˆÍA-1‚Ì‚Í‘S”ÍˆÍ
	int attack_area;//UŒ‚”ÍˆÍ
public:
	Heal();
	virtual bool effectBattle(stagedata, Player**, int, int, Enemy**, int);
	virtual bool effectMap(PartyControl* pc);
};