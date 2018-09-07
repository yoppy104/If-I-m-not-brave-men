#include <cmath>
#include "Player.h"
#include "Enemy.h"
#include "Equipment.h"
#include "draw.h"
#include "DxLib.h"

typedef unsigned long long stagedata;

Player::Player(char _name[], int _hp, int _x, int _y, int _attack, int _diffence, Equipment _equipment, int _image, int dex) {
	strcpy(this->name, _name); //–¼‘O
	this->hp = _hp; //HP
	this->x = _x; //xÀ•W
	this->y = _y; //yÀ•W
	this->attack = _attack; //UŒ‚—Í
	this->diffence = _diffence; //–hŒä—Í
	this->equipment = _equipment; //‘•”õ
	this->image = _image; //‰æ‘œ
	this->dex = dex; //•q·«
}

bool Player::move(int dx, int dy, stagedata stage, Enemy enemy, Player player) {
	stagedata test = 1; //ˆÚ“®Œã‚ÌˆÊ’uÀ•W
	int test_x = dx + this->x;
	int test_y = dy + this->y;
	if ((test_x >= 496 && test_x <= 1296) && (test_y >= 136 && test_y <= 936)) {
		test *= pow(2, round((1296 - test_x) / 160));
		test *= pow(2, 6 * round(((936 - test_y) / 160)));
	}
	else {
		test = 0;
	}

	if ((test_x == enemy.getX() && test_y == enemy.getY()) || (test_x == player.getX() && test_y == player.getY())) {
		test = 0;
	}

	if (test & stage) {
		this->x = test_x;
		this->y = test_y;
		return true;
	}
	else return false;
}

void Player::battle(stagedata stage) {
}

bool Player::is_attackable(int point) {
	int is_x = 496 + 160 * (point % 10);
	int is_y = 136 + 160 * (point / 10);
	/*
	DrawFormatString(100, 100, GetColor(0, 0, 0), "%d", is_y);
	WaitTimer(100);
	*/

	if (this->equipment.getAttackable() == -1) {
		if (! (is_x == this->x && is_y == this->y)) {
			return true;
		}
		else {
			return false;
		}
	}
	else if ((is_x >= (this->x - 160 * this->equipment.getAttackable())) && (is_x <= (this->x + 160 * this->equipment.getAttackable()))) {
		if ((is_y >= (this->y - 160 * this->equipment.getAttackable())) && (is_y <= (this->y + 160 * this->equipment.getAttackable()))) {
			/*
			DrawFormatString(100, 300, GetColor(0, 0, 0), "test");
			WaitTimer(100);
			*/
			if (is_x != this->x || is_y != this->y) {
				return true;
			}
		}
	}
	return false;
}

int Player::getDex() {
	return this->dex;
}
int Player::getX() {
	return this->x;
}
int Player::getY() {
	return this->y;
}
int Player::getImage() {
	return this->image;
}

Equipment Player::getEquipment() {
	return this->equipment;
}