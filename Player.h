#pragma once

#include "Weapon.h"
#include "Character.h"
#include <vector>
#include "Magic.h"
#include "Armor.h"

class Enemy;

using namespace std;

typedef unsigned long long stagedata;

class Player :public Character{ // プレイヤーの構造体、味方もこれで管理
protected:
	char name[10]; // 名前。これで個体を管理する

	vector <Magic*> magics;
	int image_map_front[2] = { 0,0 };
	int image_map_back[2] = { 0,0 };
	int image_map_right[4] = { 0, 0, 0, 0 };
	int image_map_left[4] = { 0, 0, 0, 0 };

	Weapon* weapon; // 装備の配列
	Armor* arm;
	Armor* head;
	Armor* chest;
	Armor* shield;

public:

	Player();
	Player(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon* _weapon, Armor* head, Armor* arm, Armor* chest, Armor* shield, int _image, int image_dead);

	~Player();

	void addMagic(Magic* new_magic);

	int getNumMagics();
	vector <Magic*> getMagics();
	Magic* getMagic(int index);

	virtual void plusMp(int);
	virtual int getMp();

	virtual int getMagicStone();
	virtual void plusMagicStone(int);

	virtual bool move(int dx, int dy, stagedata stage, Enemy** enemy, int size_enemy, Player** player, int size_player);

	virtual void battle(int attack_point, Player **p, int size_p, Enemy **e, int size_e);

	virtual bool is_attackable(int point);

	virtual Weapon* getWeapon();
	virtual Armor* getArmor(int type);

	void draw_map(int x, int y, int frame, int direction, double disp_rate);

	void setEquipment(Weapon* temp);
	void setEquipment(Armor* temp, int type);
};