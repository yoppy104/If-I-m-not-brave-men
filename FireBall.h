#pragma once
#include "Magic.h"
#include "Player.h"
#include "Enemy.h"

typedef unsigned long long stagedata;

class FireBall : public Magic {
private:
	int type;
	int damage;
	int attackable;//���S�~�͈̔́A-1�̎��͑S�͈�
	int attack_area;//�U���͈�
public:
	FireBall();
	virtual bool effectBattle(stagedata, Player**, int, int, Enemy**, int);
	virtual void effectMap();
};