#include <cmath>
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "draw.h"
#include "DxLib.h"
#include "Mathematic.h"

typedef unsigned long long stagedata;

Player::Player(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon weapon, int image):Character(name, x, y, hp, attack, diffence, magic_power, dex){
	this->weapon = weapon; //装備
	this->image = image; //画像
}

bool Player::move(int dx, int dy, stagedata stage, Enemy* enemy, Player* player) {
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

	for (int i = 0; i < sizeof(player); i++) {
		if (test_x == player->getX() && test_y == player->getY()) {
			is_p = true;
		}
		player++;
	}

	if ((test_x == enemy->getX() && test_y == enemy->getY()) || is_p) {
		test = 0;
	}

	if (test & stage) {
		this->setX(test_x);
		this->setY(test_y);
		return true;
	}
	else return false;
}

void Player::battle(int attack_point, Player *p, Enemy *e) {
	int point_x = attack_point % 10; //カーソルのx座標
	int point_y = attack_point / 10; //カーソルのy座標
	int attack_area = this->weapon.getAttackArea() / 10; //攻撃範囲
	int len = this->weapon.getAttackArea() % 10; //攻撃の長さ(1では無効)
	if (attack_area == 1) { //攻撃範囲が一点のみの場合
		// 味方へのダメージ
		if (496 + 160 * point_x == p->getX() && 136 + 160 * point_y == p->getY()) {
			int d = damage(this->getAttack() + this->weapon.getPoint(), p->getDiffence(), 1); //ダメージ計算
			p->plusHp(-d); //体力を減少
			DrawFormatString(p->getX() + 50, p->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
			WaitTimer(150);
		}
		// 敵へのダメージ
		if (496 + 160 * point_x == e->getX() && 136 + 160 * point_y == e->getY()) {
			int d = damage(this->getAttack() + this->weapon.getPoint(), e->getDiffence(), 1); //ダメージ計算
			e->plusHp(-d); //体力を減少
			DrawFormatString(e->getX() + 50, e->getY() - 32, GetColor(150, 0, 40), "%d",d); //ダメージを表記

			WaitTimer(150);
		}
	} 
	else if (attack_area == 2) {
		// x軸の正規方向ベクトル
		int delta_x = (-this->getX() + (496 + 160 * point_x) == 0) ? 0 : (-this->getX() + (496 + 160 * point_x)) / abs(-this->getX() + (496 + 160 * point_x));
		// y軸の正規方向ベクトル
		int delta_y = (-this->getY() + (136 + 160 * point_y) == 0) ? 0 : (-this->getY() + (136 + 160 * point_y)) / abs(-this->getY() + (136 + 160 * point_y));
		for (int i = 0; i < len + 1; i++) {
			//味方へのダメージ
			if (496 + 160 * (point_x + delta_x * i) == p->getX() && 136 + 160 * (point_y + delta_y * i) == p->getY()) {
				int d = damage(this->getAttack() + this->weapon.getPoint(), p->getDiffence(), 1); //ダメージ計算
				p->plusHp(-d); //体力を減少
				DrawFormatString(p->getX() + 50, p->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
				WaitTimer(150);
			}
			//敵へのダメージ
			if (496 + 160 * (point_x + delta_x * i) == e->getX() && 136 + 160 * (point_y + delta_y * i) == e->getY()) {
				int d = damage(this->getAttack() + this->weapon.getPoint(), e->getDiffence(), 1); //ダメージ計算
				e->plusHp(-d); //体力を減少
				DrawFormatString(e->getX() + 50, e->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
				WaitTimer(150);
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
			//味方へのダメージ
			if (496 + 160 * (point_x + delta_x * i) == p->getX() && 136 + 160 * (point_y + delta_y * i) == p->getY() || 496 + 160 * (point_x - delta_x * i) == p->getX() && 136 + 160 * (point_y - delta_y * i) == p->getY()) {
				int d = damage(this->getAttack() + this->weapon.getPoint(), p->getDiffence(), 1); //ダメージ計算
				p->plusHp(-d); //体力を減少
				DrawFormatString(p->getX() + 50, p->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
				WaitTimer(150);
			}
			//敵へのダメージ
			if (496 + 160 * (point_x + delta_x * i) == e->getX() && 136 + 160 * (point_y + delta_y * i) == e->getY() || 496 + 160 * (point_x - delta_x * i) == e->getX() && 136 + 160 * (point_y - delta_y * i) == e->getY()) {
				int d = damage(this->getAttack() + this->weapon.getPoint(), e->getDiffence(), 1); //ダメージ計算
				e->plusHp(-d); //体力を減少
				DrawFormatString(e->getX() + 50, e->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
				WaitTimer(150);
			}
		}
	}
	else if (attack_area == 4) {
		// 味方へのダメージ
		if (496 + 160 * (point_x - len) <= p->getX() && 496 + 160 * (point_x + len) >= p->getX()) {
			if (136 + 160 * (point_y - len) <= p->getY() && 136 + 160 * (point_y + len) >= p->getY()) {
				int d = damage(this->getAttack() + this->weapon.getPoint(), p->getDiffence(), 1); //ダメージ計算
				p->plusHp(-d); //体力を減少
				DrawFormatString(p->getX() + 50, p->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
				WaitTimer(150);
			}
		}
		// 敵へのダメージ
		if (496 + 160 * (point_x - len) <= e->getX() && 496 + 160 * (point_x + len) >= e->getX()) {
			if (136  + 160 * (point_y - len) <= e->getY() && 136 + 160 * (point_y + len) >= e->getY()) {
				int d = damage(this->getAttack() + this->weapon.getPoint(), e->getDiffence(), 1); //ダメージ計算
				e->plusHp(-d); //体力を減少
				DrawFormatString(e->getX() + 50, e->getY() - 32, GetColor(150, 0, 40), "%d", d); //ダメージを表記
				WaitTimer(150);
			}
		}
	}
}

bool Player::is_attackable(int point) {
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
	return false;
}


int Player::getImage() {
	return this->image;
}

Weapon Player::getWeapon() {
	return this->weapon;
}