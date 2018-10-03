#include <cmath>
#include "Player.h"
#include "Enemy.h"
#include "Equipment.h"
#include "draw.h"
#include "DxLib.h"
#include "Mathematic.h"

typedef unsigned long long stagedata;

Player::Player(char _name[], int _hp, int _x, int _y, int _attack, int _diffence, Equipment _equipment, int _image, int dex) {
	strcpy(this->name, _name); //���O
	this->hp_max = _hp; //HP
	this->hp = _hp;
	this->x = _x; //x���W
	this->y = _y; //y���W
	this->attack = _attack; //�U����
	this->diffence = _diffence; //�h���
	this->equipment = _equipment; //����
	this->image = _image; //�摜
	this->dex = dex; //�q����
}

bool Player::move(int dx, int dy, stagedata stage, Enemy enemy, Player player) {
	stagedata test = 1; //�ړ���̈ʒu���W
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

void Player::battle(int attack_point, Player *p, Enemy *e) {
	int point_x = attack_point % 10; //�J�[�\����x���W
	int point_y = attack_point / 10; //�J�[�\����y���W
	int attack_area = this->equipment.getAttackArea() / 10; //�U���͈�
	int len = this->equipment.getAttackArea() % 10; //�U���̒���(1�ł͖���)
	if (attack_area == 1) { //�U���͈͂���_�݂̂̏ꍇ
		// �����ւ̃_���[�W
		if (496 + 160 * point_x == p->getX() && 136 + 160 * point_y == p->getY()) {
			int d = damage(this->attack + this->equipment.getPoint(), p->getDiffence(), 1); //�_���[�W�v�Z
			p->plusHp(-d); //�̗͂�����
			DrawFormatString(p->getX() + 50, p->getY() - 32, GetColor(150, 0, 40), "%d", d); //�_���[�W��\�L
			WaitTimer(150);
		}
		// �G�ւ̃_���[�W
		if (496 + 160 * point_x == e->getX() && 136 + 160 * point_y == e->getY()) {
			int d = damage(this->attack + this->equipment.getPoint(), e->getDiffence(), 1); //�_���[�W�v�Z
			e->plusHp(-d); //�̗͂�����
			DrawFormatString(e->getX() + 50, e->getY() - 32, GetColor(150, 0, 40), "%d",d); //�_���[�W��\�L

			WaitTimer(150);
		}
	} 
	else if (attack_area == 2) {
		// x���̐��K�����x�N�g��
		int delta_x = (-this->x + (496 + 160 * point_x) == 0) ? 0 : (-this->x + (496 + 160 * point_x)) / abs(-this->x + (496 + 160 * point_x));
		// y���̐��K�����x�N�g��
		int delta_y = (-this->y + (136 + 160 * point_y) == 0) ? 0 : (-this->y + (136 + 160 * point_y)) / abs(-this->y + (136 + 160 * point_y));
		for (int i = 0; i < len + 1; i++) {
			//�����ւ̃_���[�W
			if (496 + 160 * (point_x + delta_x * i) == p->getX() && 136 + 160 * (point_y + delta_y * i) == p->getY()) {
				int d = damage(this->attack + this->equipment.getPoint(), p->getDiffence(), 1); //�_���[�W�v�Z
				p->plusHp(-d); //�̗͂�����
				DrawFormatString(p->getX() + 50, p->getY() - 32, GetColor(150, 0, 40), "%d", d); //�_���[�W��\�L
				WaitTimer(150);
			}
			//�G�ւ̃_���[�W
			if (496 + 160 * (point_x + delta_x * i) == e->getX() && 136 + 160 * (point_y + delta_y * i) == e->getY()) {
				int d = damage(this->attack + this->equipment.getPoint(), e->getDiffence(), 1); //�_���[�W�v�Z
				e->plusHp(-d); //�̗͂�����
				DrawFormatString(e->getX() + 50, e->getY() - 32, GetColor(150, 0, 40), "%d", d); //�_���[�W��\�L
				WaitTimer(150);
			}
		}
	}
	else if (attack_area == 3) {
		//x���̐��K�����x�N�g��,y���̐��K�����x�N�g��
		int delta_x = this->y + (136 + 160 * point_y);
		int delta_y = this->x + (496 + 160 * point_x);
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
			//�����ւ̃_���[�W
			if (496 + 160 * (point_x + delta_x * i) == p->getX() && 136 + 160 * (point_y + delta_y * i) == p->getY() || 496 + 160 * (point_x - delta_x * i) == p->getX() && 136 + 160 * (point_y - delta_y * i) == p->getY()) {
				int d = damage(this->attack + this->equipment.getPoint(), p->getDiffence(), 1); //�_���[�W�v�Z
				p->plusHp(-d); //�̗͂�����
				DrawFormatString(p->getX() + 50, p->getY() - 32, GetColor(150, 0, 40), "%d", d); //�_���[�W��\�L
				WaitTimer(150);
			}
			//�G�ւ̃_���[�W
			if (496 + 160 * (point_x + delta_x * i) == e->getX() && 136 + 160 * (point_y + delta_y * i) == e->getY() || 496 + 160 * (point_x - delta_x * i) == e->getX() && 136 + 160 * (point_y - delta_y * i) == e->getY()) {
				int d = damage(this->attack + this->equipment.getPoint(), e->getDiffence(), 1); //�_���[�W�v�Z
				e->plusHp(-d); //�̗͂�����
				DrawFormatString(e->getX() + 50, e->getY() - 32, GetColor(150, 0, 40), "%d", d); //�_���[�W��\�L
				WaitTimer(150);
			}
		}
	}
	else if (attack_area == 4) {
		// �����ւ̃_���[�W
		if (496 + 160 * (point_x - len) <= p->getX() && 496 + 160 * (point_x + len) >= p->getX()) {
			if (136 + 160 * (point_y - len) <= p->getY() && 136 + 160 * (point_y + len) >= p->getY()) {
				int d = damage(this->attack + this->equipment.getPoint(), p->getDiffence(), 1); //�_���[�W�v�Z
				p->plusHp(-d); //�̗͂�����
				DrawFormatString(p->getX() + 50, p->getY() - 32, GetColor(150, 0, 40), "%d", d); //�_���[�W��\�L
				WaitTimer(150);
			}
		}
		// �G�ւ̃_���[�W
		if (496 + 160 * (point_x - len) <= e->getX() && 496 + 160 * (point_x + len) >= e->getX()) {
			if (136  + 160 * (point_y - len) <= e->getY() && 136 + 160 * (point_y + len) >= e->getY()) {
				int d = damage(this->attack + this->equipment.getPoint(), e->getDiffence(), 1); //�_���[�W�v�Z
				e->plusHp(-d); //�̗͂�����
				DrawFormatString(e->getX() + 50, e->getY() - 32, GetColor(150, 0, 40), "%d", d); //�_���[�W��\�L
				WaitTimer(150);
			}
		}
	}
}

bool Player::is_attackable(int point) {
	int is_x = 496 + 160 * (point % 10);
	int is_y = 136 + 160 * (point / 10);

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

int Player::getDiffence() {
	return this->diffence;
}

int Player::getHp() {
	return this->hp;
}

void Player::plusHp(int point) {
	this->hp += point;
}

Equipment Player::getEquipment() {
	return this->equipment;
}