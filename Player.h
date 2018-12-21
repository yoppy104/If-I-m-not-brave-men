#pragma once

#include "Weapon.h"
#include "Character.h"
#include <vector>
#include "Magic.h"

class Enemy;

using namespace std;

typedef unsigned long long stagedata;

class Player :public Character{ // �v���C���[�̍\���́A����������ŊǗ�
protected:
	char name[10]; // ���O�B����Ō̂��Ǘ�����
	Weapon* weapon; // �����̔z��
	vector <Magic*> magics;
	int image_map_front[2] = { 0,0 };
	int image_map_back[2] = { 0,0 };
	int image_map_right[4] = { 0, 0, 0, 0 };
	int image_map_left[4] = { 0, 0, 0, 0 };

public:

	Player();
	Player(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon* _weapon, int _image, int image_dead);

	void addMagic(Magic* new_magic);

	int getNumMagics();
	vector<Magic*> getMagics();

	virtual void plusMp(int);
	virtual int getMp();

	virtual int getMagicStone();
	virtual void plusMagicStone(int);

	virtual bool move(int dx, int dy, stagedata stage, Enemy** enemy, int size_enemy, Player** player, int size_player);

	virtual void battle(int attack_point, Player **p, int size_p, Enemy **e, int size_e);

	virtual bool is_attackable(int point);

	virtual Weapon* getWeapon();

	void draw_map(int x, int y, int frame, int direction);

};