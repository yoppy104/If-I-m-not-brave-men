#include "Magic.h"
#include "FireBall.h"
#include "draw.h"

typedef unsigned long long stagedata;

FireBall::FireBall() :Magic(1, "ファイアボール", 5, false) {
	this->damage = 10;
	this->type = 1;
	this->attack_area = 11;
	this->attackable = 2;
}

bool FireBall::effectBattle(stagedata stage, Player** players, int user, int size_players, Enemy** enemy, int size_enemy) {
	return false;
}

void FireBall::effectMap() {
	DrawFormatString(100, 100, GetColor(0, 0, 0), "test");
}