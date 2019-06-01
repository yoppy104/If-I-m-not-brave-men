#include "Character.h"



Character::Character(ID id, int xpos, int ypos) :
	id(id),
	name("NULL"),
	pos{ xpos, ypos },
	status{},
	hasMp(true),
	is_moveable(true),
	images{}
{

}


void Character::down() {
	is_moveable = false;
}

void Character::alive() {
	is_moveable = true;
}

void Character::plusHp() {
	status.hp = status.hpMax;
}

void Character::plusMp() {
	status.mp = status.mpMax;
}

void Character::plusHp(int point) {
	status.hp += point;
	if (status.hp > status.hpMax) {
		status.hp = status.hpMax;
	}
}

void Character::plusMp(int point) {
	status.mp += point;
	if (status.mp > status.mpMax) {
		status.mp = status.mpMax;
	}
}

void Character::setHasMp(bool d) {
	hasMp = d;
}

//Player用
void Character::move() {
	DrawFormatString(100, 100, GetColor(0, 0, 0), "オーバーライドしてください");
}
void Character::battle() {
	DrawFormatString(100, 100, GetColor(0, 0, 0), "オーバーライドしてください");
}
bool Character::is_attackable() {
	DrawFormatString(100, 100, GetColor(0, 0, 0), "オーバーライドしてください");
	return false;
}