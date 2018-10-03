
#include "Enemy.h"
#include "Player.h"
#include "DxLib.h"
#include "draw.h"
#include <cstdlib>
#include <cmath>

using namespace std;

Enemy::Enemy(char _name[], int _hp, int _x, int _y, int _attack, int _diffence, int _image) { // ‰Šú‰»
	strcpy(this->name, _name);
	this->hp = _hp;
	this->hp_max = _hp;
	this->x = _x;
	this->y = _y;
	this->attack = _attack;
	this->diffence = _diffence;
	this->image = _image;
}

void Enemy::move(Player* p, Enemy* e, int background_image, stagedata stage) { // “G‚ÌˆÚ“®
	
}

int Enemy::getX() {
	return this->x;
}

int Enemy::getY() {
	return this->y;
}

int Enemy::getAttack() {
	return this->attack;
}

int Enemy::getDiffence() {
	return this->diffence;
}

int Enemy::getHp() {
	return this->hp;
}

void Enemy::plusHp(int dp) {
	this->hp += dp;
}

int Enemy::getImage() {
	return this->image;
}