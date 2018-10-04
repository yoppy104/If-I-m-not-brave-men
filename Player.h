#pragma once

#include "Weapon.h"

class Enemy;

using namespace std;

typedef unsigned long long stagedata;

class Player { // �v���C���[�̍\���́A����������ŊǗ�
	char name[10]; // ���O�B����Ō̂��Ǘ�����
	int hp_max; // �̗�
	int hp;
	int x; // �L������x���W
	int y; // �L������y���W
	int attack; // �L�����̍U����
	int diffence; // �L�����̖h���
	int dex;
	Weapon weapon; // �����̔z��
	int image; // �摜

public:
	Player(char _name[], int _hp, int _x, int _y, int _attack, int _diffence, Weapon _weapon, int _image, int dex);

	bool move(int dx, int dy, stagedata data, Enemy enemy, Player player);

	void battle(int attack_point, Player *p, Enemy *e);

	bool is_attackable(int point);

	int getDex();
	int getX();
	int getY();
	int getImage();
	int getDiffence();
	int getHp();
	void plusHp(int point);
	Weapon getWeapon();

};