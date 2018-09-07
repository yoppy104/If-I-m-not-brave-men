#pragma once

#include "Equipment.h"

class Enemy;

using namespace std;

typedef unsigned long long stagedata;

class Player { // �v���C���[�̍\���́A����������ŊǗ�
	char name[10]; // ���O�B����Ō̂��Ǘ�����
	int hp; // �̗�
	int x; // �L������x���W
	int y; // �L������y���W
	int attack; // �L�����̍U����
	int diffence; // �L�����̖h���
	int dex;
	Equipment equipment; // �����̔z��
	int image; // �摜

public:
	Player(char _name[], int _hp, int _x, int _y, int _attack, int _diffence, Equipment _equipment, int _image, int dex);

	bool move(int dx, int dy, stagedata data, Enemy enemy, Player player);

	void battle(stagedata data);

	bool is_attackable(int point);

	int getDex();
	int getX();
	int getY();
	int getImage();
	Equipment getEquipment();

};