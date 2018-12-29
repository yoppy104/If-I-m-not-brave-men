#include <cmath>
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "draw.h"
#include "DxLib.h"
#include "Mathematic.h"
#include <fstream>
#include "Items.h"

typedef unsigned long long stagedata;

typedef struct {
	int exp;
	int weapon;
	int shield;
	int chest;
	int arm;
	int head;
} SaveData;

Player::Player() {

}

Player::Player(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon* weapon, Armor* head, Armor* arm, Armor* chest, Armor* shield, int image, int image_dead):Character(name, x, y, hp, attack, diffence, magic_power, dex, image, image_dead){
	this->weapon = weapon; //装備
	this->head = head;
	this->arm = arm;
	this->shield = shield;
	this->chest = chest;
	this->exp = 0;
	this->Lv = 1;
}

Player::Player(char name[], int x, int y) :Character() {
	this->x = x;
	this->y = y;
	strcpy(this->name, name);
	SaveData data;
	fstream file;
	file.open("playerdata.dat", ios::binary | ios::in);
	file.read((char*)&data, sizeof(data));
	file.close();
	this->exp = data.exp;
	if (data.weapon == NOTEQUIPMENT) {
		this->weapon = new NonWeapon();
	}
	else {
		this->weapon = (Weapon*)search(data.weapon);
	}
	if (data.shield == NOTEQUIPMENT) {
		this->shield = new NonShield();
	}
	else {
		this->shield = (Armor*)search(data.shield);
	}
	if (data.chest == NOTEQUIPMENT) {
		this->chest = new NonChest();
	}
	else {
		this->chest = (Armor*)search(data.chest);
	}
	if (data.arm == NOTEQUIPMENT) {
		this->arm = new NonArm();
	}
	else {
		this->arm = (Armor*)search(data.arm);
	}
	if (data.head == NOTEQUIPMENT) {
		this->head = new NonHead();
	}
	else {
		this->head = (Armor*)search(data.head);
	}
}

Player::~Player() {
	this->magics.clear();
}

void Player::levelup() {

}

void Player::addMagic(Magic* new_magic) {
	this->magics.push_back(new_magic);
}

int Player::getNumMagics() {
	return this->magics.size();
}

vector <Magic*> Player::getMagics() {
	return this->magics;
}

Magic* Player::getMagic(int index) {
	return this->magics[index];
}

int Player::getMagicStone() {
	return 0;
}
void Player::plusMagicStone(int point) {

}

int Player::getLv() {
	return this->Lv;
}

bool Player::move(int dx, int dy, stagedata stage, Enemy** enemy, int size_enemy, Player** player, int size_player) {
	stagedata test = 1; //移動後の位置座標
	int test_x = dx + this->getX();
	int test_y = dy + this->getY();
	if ((test_x >= 496 && test_x <= 1296) && (test_y >= 136 && test_y <= 936)) {
		test *= pow(2, round((1296 - test_x) / 160));
		test *= pow(2, 6 * round(((936 - test_y) / 160)));
	}
	else {
		test = 0;
	}

	bool is_p, is_e;
	is_p = false;
	is_e = false;

	for (int i = 0; i < size_player; i++) {
		if (test_x == player[i]->getX() && test_y == player[i]->getY()) {
			is_p = true;
		}
	}

	for (int i = 0; i < size_enemy; i++) {
		if (test_x == enemy[i]->getX() && test_y == enemy[i]->getY()) {
			is_e = true;
		}
	}

	if (is_e || is_p) {
		test = 0;
	}

	if (test & stage) {
		this->setX(test_x);
		this->setY(test_y);
		return true;
	}
	else return false;
}

void Player::battle(int attack_point, Player **p, int size_p, Enemy **e, int size_e) {
	/*
	int point_x = attack_point % 10; //カーソルのx座標
	int point_y = attack_point / 10; //カーソルのy座標
	int attack_area = this->weapon.getAttackArea() / 10; //攻撃範囲
	int len = this->weapon.getAttackArea() % 10; //攻撃の長さ(1では無効)
	int image = LoadGraph("damage.png");

	if (496 + 160 * point_x != this->getX() || 136 + 160 * point_y != this->getY()) {
		if (attack_area == 1) { //攻撃範囲が一点のみの場合
			// 味方へのダメージ
			for (int i = 0; i < size_p; i++) {
				if (496 + 160 * point_x == p[i]->getX() && 136 + 160 * point_y == p[i]->getY()) {
					int d = damage(this->getAttack() + this->weapon.getPoint(), p[i]->getDiffence(), 1); //ダメージ計算
					p[i]->plusHp(-d); //体力を減少
					DrawGraph(p[i]->getX() + 32, p[i]->getY() - 48, image, TRUE);
					DrawFormatString(p[i]->getX() + 50, p[i]->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
					WaitTimer(150);
				}
			}
			// 敵へのダメージ
			for (int i = 0; i < size_e; i++) {
				if (496 + 160 * point_x == e[i]->getX() && 136 + 160 * point_y == e[i]->getY()) {
					int d = damage(this->getAttack() + this->weapon.getPoint(), e[i]->getDiffence(), 1); //ダメージ計算
					e[i]->plusHp(-d); //体力を減少
					DrawGraph(e[i]->getX() + 32, e[i]->getY() - 48, image, TRUE);
					DrawFormatString(e[i]->getX() + 50, e[i]->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
					WaitTimer(150);
				}
			}
		}
		else if (attack_area == 2) {
			// x軸の正規方向ベクトル
			int delta_x = (-this->getX() + (496 + 160 * point_x) == 0) ? 0 : (-this->getX() + (496 + 160 * point_x)) / abs(-this->getX() + (496 + 160 * point_x));
			// y軸の正規方向ベクトル
			int delta_y = (-this->getY() + (136 + 160 * point_y) == 0) ? 0 : (-this->getY() + (136 + 160 * point_y)) / abs(-this->getY() + (136 + 160 * point_y));
			for (int j = 0; j < len + 1; j++) {
				//味方へのダメージ

				for (int i = 0; i < size_p; i++) {
					if (496 + 160 * (point_x + delta_x * j) == p[i]->getX() && 136 + 160 * (point_y + delta_y * j) == p[i]->getY()) {
						int d = damage(this->getAttack() + this->weapon.getPoint(), p[i]->getDiffence(), 1); //ダメージ計算
						p[i]->plusHp(-d); //体力を減少
						DrawGraph(p[i]->getX() + 32, p[i]->getY() - 48, image, TRUE);
						DrawFormatString(p[i]->getX() + 50, p[i]->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
						WaitTimer(150);
					}
				}
				//敵へのダメージ
				for (int i = 0; i < size_e; i++) {
					if (496 + 160 * (point_x + delta_x * j) == e[i]->getX() && 136 + 160 * (point_y + delta_y * j) == e[i]->getY()) {
						int d = damage(this->getAttack() + this->weapon.getPoint(), e[i]->getDiffence(), 1); //ダメージ計算
						e[i]->plusHp(-d); //体力を減少
						DrawGraph(e[i]->getX() + 32, e[i]->getY() - 48, image, TRUE);
						DrawFormatString(e[i]->getX() + 50, e[i]->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
						WaitTimer(150);
					}
				}
			}
		}
		else if (attack_area == 3) {
			//x軸の正規方向ベクトル,y軸の正規方向ベクトル
			int delta_x = this->getY() + (136 + 160 * point_y);
			int delta_y = this->getX() + (496 + 160 * point_x);
			if (delta_x == 0) delta_y = 1;
			if (delta_y == 0) delta_x = 1;
			if ((delta_x < 0 && delta_y < 0) || (delta_x > 0 && delta_y > 0)) {
				delta_x = 1;
				delta_y = -1;
			}
			else if ((delta_x < 0 && delta_y > 0) || (delta_x > 0 && delta_y < 0)) {
				delta_x = 1;
				delta_y = 1;
			}
			for (int i = 0; i < len + 1; i++) {
				for (int j = 0; j < size_p; j++) {
					//味方へのダメージ
					if (496 + 160 * (point_x + delta_x * i) == p[j]->getX() && 136 + 160 * (point_y + delta_y * i) == p[j]->getY() || 496 + 160 * (point_x - delta_x * i) == p[j]->getX() && 136 + 160 * (point_y - delta_y * i) == p[j]->getY()) {
						int d = damage(this->getAttack() + this->weapon.getPoint(), p[j]->getDiffence(), 1); //ダメージ計算
						p[j]->plusHp(-d); //体力を減少
						DrawGraph(p[i]->getX() + 32, p[i]->getY() - 48, image, TRUE);
						DrawFormatString(p[j]->getX() + 50, p[j]->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
						WaitTimer(150);
					}
				}
				//敵へのダメージ
				for (int j = 0; j < size_e; j++) {
					if (496 + 160 * (point_x + delta_x * i) == e[j]->getX() && 136 + 160 * (point_y + delta_y * i) == e[j]->getY() || 496 + 160 * (point_x - delta_x * i) == e[j]->getX() && 136 + 160 * (point_y - delta_y * i) == e[j]->getY()) {
						int d = damage(this->getAttack() + this->weapon.getPoint(), e[j]->getDiffence(), 1); //ダメージ計算
						e[j]->plusHp(-d); //体力を減少
						DrawGraph(e[i]->getX() + 32, e[i]->getY() - 48, image, TRUE);
						DrawFormatString(e[j]->getX() + 50, e[j]->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
						WaitTimer(150);
					}
				}
			}
		}
		else if (attack_area == 4) {
			// 味方へのダメージ
			for (int i = 0; i < size_p; i++) {
				if (496 + 160 * (point_x - len) <= p[i]->getX() && 496 + 160 * (point_x + len) >= p[i]->getX()) {
					if (136 + 160 * (point_y - len) <= p[i]->getY() && 136 + 160 * (point_y + len) >= p[i]->getY()) {
						int d = damage(this->getAttack() + this->weapon.getPoint(), p[i]->getDiffence(), 1); //ダメージ計算
						p[i]->plusHp(-d); //体力を減少
						DrawGraph(p[i]->getX() + 32, p[i]->getY() - 48, image, TRUE);
						DrawFormatString(p[i]->getX() + 50, p[i]->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
						WaitTimer(150);
					}
				}
			}
			// 敵へのダメージ
			for (int i = 0; i < size_e; i++) {
				if (496 + 160 * (point_x - len) <= e[i]->getX() && 496 + 160 * (point_x + len) >= e[i]->getX()) {
					if (136 + 160 * (point_y - len) <= e[i]->getY() && 136 + 160 * (point_y + len) >= e[i]->getY()) {
						int d = damage(this->getAttack() + this->weapon.getPoint(), e[i]->getDiffence(), 1); //ダメージ計算
						e[i]->plusHp(-d); //体力を減少
						DrawGraph(e[i]->getX() + 32, e[i]->getY() - 48, image, TRUE);
						DrawFormatString(e[i]->getX() + 50, e[i]->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
						WaitTimer(150);
					}
				}
			}
		}
	}*/
}

bool Player::is_attackable(int point) {
	/*
	int is_x = 496 + 160 * (point % 10);
	int is_y = 136 + 160 * (point / 10);

	if (this->weapon.getAttackable() == -1) {
		if (! (is_x == this->getX() && is_y == this->getY())) {
			return true;
		}
		else {
			return false;
		}
	}
	else if ((is_x >= (this->getX() - 160 * this->weapon.getAttackable())) && (is_x <= (this->getX() + 160 * this->weapon.getAttackable()))) {
		if ((is_y >= (this->getY() - 160 * this->weapon.getAttackable())) && (is_y <= (this->getY() + 160 * this->weapon.getAttackable()))) {
			if (is_x != this->getX() || is_y != this->getY()) {
				return true;
			}
		}
	}
	return false;*/
	return 0;
}

Weapon* Player::getWeapon() {
	return this->weapon;
}

Armor* Player::getArmor(int type) {
	switch (type) {
	case 2:
		return this->shield;
		break;
	case 3:
		return this->chest;
		break;
	case 4:
		return this->arm;
		break;
	case 5:
		return this->head;
		break;
	}
}

void Player::plusMp(int point) {

}

void Player::plusMp() {

}

int Player::getMpMax() {
	return 0;
}

void Player::healHp(int delta) {
	this->hp += delta;
	if (this->hp > this->hp_max) {
		this->hp = this->hp_max;
	}
}

void Player::healHp() {
	this->hp = this->hp_max;
}

int Player::getMp() {
	return 3;
}

int Player::getId() {
	return this->id;
}

void Player::draw_map(int x, int y, int frame, int direction, double disp_rate) {
	switch (direction) {
	case 0:
		DrawExtendGraph(x, y, x + 64 * disp_rate, y + 64 * disp_rate, this->image_map_front[frame], TRUE);
		break;
	case 1:
		DrawExtendGraph(x, y, x + 64 * disp_rate, y + 64 * disp_rate, this->image_map_back[frame], TRUE);
		break;
	case 2:
		DrawExtendGraph(x, y, x + 64 * disp_rate, y + 64 * disp_rate, this->image_map_left[frame], TRUE);
		break;
	case 3:
		DrawExtendGraph(x, y, x + 64 * disp_rate, y + 64 * disp_rate, this->image_map_right[frame], TRUE);
		break;
	}
}

void Player::setEquipment(Weapon* temp) {
	this->weapon = temp;
}

void Player::setEquipment(Armor* temp, int type) {
	switch (type) {
	case 2:
		this->shield = temp;
		break;
	case 3:
		this->chest = temp;
		break;
	case 4:
		this->arm = temp;
		break;
	case 5:
		this->head = temp;
		break;
	}
}

int Player::calcurateEXP() {
	int result = this->exp;
	for (int i = 1; i < this->Lv; i++) {
		result += (int)150 * pow(i, 5.0 / 4.0);
	}
	return result;
}

void Player::save() {
	fstream file;
	SaveData data = { this->exp, this->weapon->getId(), this->shield->getId(), this->chest->getId(), this->arm->getId(), this->head->getId()};
	file.open("playerdata.dat", ios::binary | ios::out);
	file.write((const char *)&data, sizeof(data));
	file.close();
}