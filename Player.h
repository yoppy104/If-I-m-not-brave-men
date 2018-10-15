#pragma once

#include "Weapon.h"
#include "Character.h"

class Enemy;

using namespace std;

typedef unsigned long long stagedata;

class Player :public Character{ // �v���C���[�̍\���́A����������ŊǗ�
	char name[10]; // ���O�B����Ō̂��Ǘ�����
	Weapon weapon; // �����̔z��
	int image; // �摜

public:
	Player(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon _weapon, int _image);

	virtual bool move(int dx, int dy, stagedata stage, Enemy* enemy, int size_enemy, Player* player, int size_player);

	virtual void battle(int attack_point, Player *p, int size_p, Enemy *e, int size_e);

	virtual bool is_attackable(int point);

	virtual int getImage();
	virtual Weapon getWeapon();

};