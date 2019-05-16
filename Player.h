#pragma once

#include "Character.h"
#include <vector>
#include "Magic.h"
#include "Item.h"
#include <memory>
#include <array>

#define FIRST_EXP 0

class Enemy;
class Magic;

typedef struct {
	unique_ptr<Item> weapon; //武器
	unique_ptr<Item> arm;	 //籠手
	unique_ptr<Item> head;	 //兜
	unique_ptr<Item> chest;	 //胸当て
	unique_ptr<Item> shield; //盾
} Equipment;

typedef struct {
	int allEXP;		//全経験値
	int NextEXP;	//次回レベルアップまでの経験値
	int stuckEXP;	//累積経験値
} EXP;

using namespace std;

class Player :public Character{ // プレイヤーの構造体、味方もこれで管理
protected:
	vector <unique_ptr<Magic>> magics;
	EXP exp;

	int LV;
	int charAniframe;
	int StaWindow;
	int Font;
	bool active;
	bool Block;
	
	Equipment equipment;

	int magicStone; // 魔石の所持数


public:
	Player() = default;
	Player(ID id, int x, int y); // idによるコンストラクタ

	~Player();

	virtual int sendEXp(int EXp);

	int getMagicStone() { return magicStone; }
	void plusMagicStone(int);

	void addMagic(ID id);
	int getNumMagics() { return magics.size(); }
	vector <unique_ptr<Magic>> getMagics() { return magics; }
	int getAttack();
	int getDiffence();

	void healHp(int delta);
	void healHp();

	void draw_map(int x, int y, int frame, int direction);

	void setEquipment(ID id, int type);

	bool hasEquip(int ind) {
		switch (ind) {
		case 1:
			return equipment.weapon->getId() != NOTEQUIPMENT;
			break;
		case 2:
			return equipment.shield->getId() != NOTEQUIPMENT;
			break;
		case 3:
			return equipment.chest->getId() != NOTEQUIPMENT;
			break;
		case 4:
			return equipment.arm->getId() != NOTEQUIPMENT;
			break;
		case 5:
			return equipment.head->getId() != NOTEQUIPMENT;
			break;
		} 
	}
	ID getWeaponId() { return equipment.weapon->getId(); }
	ID getArmorId(int ind) {
		switch (ind) {
		case 2:
			return equipment.shield->getId();
			break;
		case 3:
			return equipment.chest->getId();
			break;
		case 4:
			return equipment.arm->getId();
			break;
		case 5:
			return equipment.head->getId();
			break;
		}
	}
	int getEquipPoint(int type) {
		switch (type) {
		case 1:
			return equipment.weapon->getPoint();
			break;
		case 2:
			return equipment.shield->getPoint();
			break;
		case 3:
			return equipment.chest->getPoint();
			break;
		case 4:
			return equipment.arm->getPoint();
			break;
		case 5:
			return equipment.head->getPoint();
			break;
		default:
			return 0;
			break;
		}
	}
	void getEquipName(int type, int x, int y) {
		switch (type) {
		case 1:
			equipment.weapon->getName(x, y);
			break;
		case 2:
			equipment.shield->getName(x, y);
			break;
		case 3:
			equipment.chest->getName(x, y);
			break;
		case 4:
			equipment.arm->getName(x, y);
			break;
		case 5:
			equipment.head->getName(x, y);
			break;
		default:
			break;
		}
	}

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