#pragma once
#include "Magic.h"

class Heal : public Magic {
private:
	int type;
	int point;
	int attackable;//���S�~�͈̔́A-1�̎��͑S�͈�
	int attack_area;//�U���͈�
public:
	Heal();
	virtual bool effectBattle(stagedata, Player**, int, int, Enemy**, int);
	virtual bool effectMap(PartyControl* pc);
};