#include "Character.h"

using namespace std;

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
	this->is_moveable = false;
}

void Character::alive() {
	this->is_moveable = true;
}

void Character::plusHp() {
	this->status.hp = this->status.hpMax;
}

void Character::plusMp() {
	this->status.mp = this->status.mpMax;
}

void Character::plusHp(int point) {
	this->status.hp += point;
	if (this->status.hp > this->status.hpMax) {
		this->status.hp = this->status.hpMax;
	}
}

void Character::plusMp(int point) {
	this->status.mp += point;
	if (this->status.mp > this->status.mpMax) {
		this->status.mp = this->status.mpMax;
	}
}

void Character::setHasMp(bool d) {
	this->hasMp = d;
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
shared_ptr<Weapon> Character::getWeapon() {
	DrawFormatString(100, 100, GetColor(0, 0, 0), "オーバーライドしてください");
	shared_ptr<Weapon> none;
	return none;
}