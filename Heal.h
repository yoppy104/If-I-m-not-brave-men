#pragma once
#include "Magic.h"

class Heal : public Magic {
private:
	int type;
	int damage;
	int attackable;//���S�~�͈̔́A-1�̎��͑S�͈�
	int attack_area;//�U���͈�
	virtual void effectpoint(int, Player**, int, Enemy**, int);
public:
	Heal();
	virtual bool effectBattle(stagedata, Player**, int, int, Enemy**, int);
	virtual void effectMap();
};