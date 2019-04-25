#pragma once
#include "Magic.h"
#include "Player.h"
#include "Enemy.h"

typedef unsigned long long stagedata;

class FireBall : public Magic {
private:
	int type;
	int damage;
	int attackable;//“¯S‰~‚Ì”ÍˆÍA-1‚Ì‚Í‘S”ÍˆÍ
	int attack_area;//UŒ‚”ÍˆÍ
public:
	FireBall();
	virtual bool effectBattle(stagedata, Player**, int, int, Enemy**, int);
	virtual void effectMap();
};