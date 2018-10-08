#pragma once

#include "Weapon.h"
#include "Character.h"

class Enemy;

using namespace std;

typedef unsigned long long stagedata;

class Player :public Character{ // プレイヤーの構造体、味方もこれで管理
	char name[10]; // 名前。これで個体を管理する
	Weapon weapon; // 装備の配列
	int image; // 画像

public:
	Player(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon _weapon, int _image);

	bool move(int dx, int dy, stagedata data, Enemy* enemy, Player* player);

	void battle(int attack_point, Player *p, Enemy *e);

	bool is_attackable(int point);

	int getImage();
	Weapon getWeapon();

};