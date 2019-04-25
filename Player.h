#pragma once

#include "Weapon.h"
#include "Character.h"
#include <vector>
#include "Magic.h"
#include "Armor.h"
#include <memory>

#include <array>

#define FIRST_EXP 0

class Enemy;
class Magic;

using namespace std;

typedef unsigned long long stagedata;

class Player :public Character{ // プレイヤーの構造体、味方もこれで管理
protected:
	vector <Magic*> magics;

	int LV;
	int allEXP;
	int NextEXP;
	int stuckEXP;
	int gra[2], AllenAttack[4], Allendamage[8], AllenWalk[4];//グラフィックハンドル格納（とりあえず）
	int charAniframe;
	int StaWindow;
	int Font;
	bool active;
	bool Block;

	Weapon* weapon; // 装備の配列
	Armor* arm;
	Armor* head;
	Armor* chest;
	Armor* shield;

	int id; // id情報
	
	bool has_mp; // mpを所持しているかどうか
	int mp; // 現在のmp
	int mp_max; // mpの最大値

	int magicstone; // 魔石の所持数


public:
	Player();
	Player(string name, int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon* _weapon, Armor* head, Armor* arm, Armor* chest, Armor* shield, int _image, int image_dead);
	Player(string name, int x, int y);
	Player(int id, int x, int y); // idによるコンストラクタ

	~Player();

	virtual int getMp();
	virtual int getMpMax();
	virtual void plusMp(int);
	virtual void plusMp();
	virtual int sendEXp(int EXp);

	virtual int getMagicStone();
	virtual void plusMagicStone(int);

	void addMagic(Magic* new_magic);
	int getId();
	int getNumMagics();
	vector <Magic*> getMagics();
	Magic* getMagic(int index);
	virtual int getAttack();
	virtual int getDiffence();

	void healHp(int delta);
	void healHp();

	virtual Weapon* getWeapon();
	virtual Armor* getArmor(int type);

	void draw_map(int x, int y, int frame, int direction);

	void setEquipment(Weapon* temp);
	void setEquipment(Armor* temp, int type);

	int DrawSta(double x, double y);
	int ActBlock();
	int ReleaseBlock();
	int SetAniframe(int x);
	int GetLV();
	bool GetActive();
	bool Activate();
	int DrawChar(double x, double y, int scene);
	int GetAGI();
	int Damage(int x);
};