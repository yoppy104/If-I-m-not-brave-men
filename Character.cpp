#include "Character.h"
#include "DxLib.h"
#include <string.h>

Character::Character() {

}

Character::Character(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex) {
	strcpy(this->name, name);
	this->x = x;
	this->y = y;
	this->hp = hp;
	this->hp_max = hp;
	this->attack = attack;
	this->diffence = diffence;
	this->magic_power = magic_power;
	this->dex = dex;
}

void Character::getName(int x, int y) {
	DrawFormatString(x, y, GetColor(0,0,0), this->name);
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