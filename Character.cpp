#include "Character.h"
#include "DxLib.h"
#include <string.h>

using namespace std;

Character::Character() :
	name(NULL),
	x(NULL),
	y(NULL),
	hp(NULL),
	attack(NULL),
	diffence(NULL),
	magic_power(NULL),
	dex(NULL),
	image(NULL),
	image_dead(NULL),
	has_mp(true),
	is_moveable(true),
	image_map_back{ NULL, NULL },
	image_map_front{ NULL, NULL},
	image_map_right{NULL, NULL, NULL, NULL},
	image_map_left{NULL, NULL, NULL, NULL}
{

}

Character::Character(int x, int y) :
	name(NULL),
	x(x),//エラー位置
	y(y),
	hp(NULL),
	attack(NULL),
	diffence(NULL),
	magic_power(NULL),
	dex(NULL),
	image(NULL),
	image_dead(NULL),
	has_mp(true),
	is_moveable(true),
	image_map_back{ NULL, NULL },
	image_map_front{ NULL, NULL },
	image_map_right{ NULL, NULL, NULL, NULL },
	image_map_left{ NULL, NULL, NULL, NULL }
{

}

Character::Character(string name, int x, int y, int hp, int attack, int diffence, int magic_power, int dex, int image, int image_dead) {
	name = name;
	this->x = x;
	this->y = y;
	this->hp = hp;
	this->hp_max = hp;
	this->attack = attack;
	this->diffence = diffence;
	this->magic_power = magic_power;
	this->dex = dex;
	this->has_mp = true;
	this->image = image;
	this->image_dead = image_dead;
	this->is_moveable = true;
}

void Character::down() {
	this->is_moveable = false;
}

void Character::alive() {
	this->is_moveable = true;
}

int Character::getIsMoveable() {
	return this->is_moveable;
}

void Character::getName(int x, int y, int col) {
	DrawFormatString(x, y, col, this->name.c_str());
}

int Character::getX() {
	return this->x;
}

void Character::setX(int dx) {
	this->x = dx;
}

int Character::getY() {
	return this->y;
}

void Character::setY(int dy) {
	this->y = dy;
}

int Character::getHp() {
	return this->hp;
}

int Character::getHpMax() {
	return this->hp_max;
}

void Character::plusHp(int point) {
	this->hp += point;
}

int Character::getAttack() {
	return this->attack;
}

int Character::getDiffence() {
	return this->diffence;
}

int Character::getMagicPower() {
	return this->magic_power;
}

int Character::getDex() {
	return this->dex;
}

bool Character::getHasMp() {
	return this->has_mp;
}

void Character::setHasMp(bool d) {
	this->has_mp = d;
}

//Allen用
int Character::getMp() {
	DrawFormatString(100, 100, GetColor(0, 0, 0), "オーバーライドしてください");
	return 0;
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
int Character::getImage() {
	return this->image;
}
int Character::getImageDead() {
	return this->image_dead;
}
Weapon* Character::getWeapon() {
	DrawFormatString(100, 100, GetColor(0, 0, 0), "オーバーライドしてください");
	Weapon* none;
	return none;
}