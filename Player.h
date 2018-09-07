#pragma once

#include "Equipment.h"

class Enemy;

using namespace std;

typedef unsigned long long stagedata;

class Player { // プレイヤーの構造体、味方もこれで管理
	char name[10]; // 名前。これで個体を管理する
	int hp; // 体力
	int x; // キャラのx座標
	int y; // キャラのy座標
	int attack; // キャラの攻撃力
	int diffence; // キャラの防御力
	int dex;
	Equipment equipment; // 装備の配列
	int image; // 画像

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