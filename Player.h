#pragma once
#include <vector>
#include <memory>
#include <array>
#include "Character.h"
#include "Item.h"
#include "Magic.h"

#define FIRST_EXP 0

typedef std::shared_ptr<Magic> magic_ptr;
typedef std::shared_ptr<Item> item_ptr;

typedef struct {
	item_ptr weapon; //武器
	item_ptr arm;	 //籠手
	item_ptr head;	 //兜
	item_ptr chest;	 //胸当て
	item_ptr shield; //盾
} Equipment;

typedef struct {
	int allEXP;		//全経験値
	int NextEXP;	//次回レベルアップまでの経験値
	int stuckEXP;	//累積経験値
} EXP;

class Player :public Character{ // プレイヤーの構造体、味方もこれで管理
protected:
	std::vector <magic_ptr> magics;
	int numMagicMap;

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

	virtual int sendEXp(int EXp);

	int getMagicStone() { return magicStone; }
	void plusMagicStone(int);

	void addMagic(ID id);
	int getNumMagicMap() { return numMagicMap; }
	int getNumMagics() { return magics.size(); }
	magic_ptr getMagic(int index) { return magics[index]; }
	std::vector<magic_ptr> getMagics() { return magics; }


	//Magic関連一応残す
	/*
	void getMagicInfo(int index, int x, int y, bool isMapOnly) {
		if (isMapOnly) {
			for (int i = 0; i < magics.size(); i++) {
				if (magics[index + i]->getIsMap()) {
					magics[index]->getName(x, y);
					break;
				}
			}
		}
		else {
			magics[index]->getName(x, y);
		}
	}
	bool getMagicIsMap(int index) {
		return magics[index]->getIsMap();
	}
	int getNumMagicMap() {
		return numMagicMap;
	}

	int useMagicMap(int index, const std::shared_ptr<PartyControl> pc) {
		if (magics[index]->getCost() > status.mp) {
			return -1;
		}
		if (magics[index]->effectMap(pc)) {
			status.mp -= magics[index]->getCost();
			return 1;
		}
		else {
			return 0;
		}
	}
	void useMagicBattle(int index) {
		magics[index]->effectBattle();
		status.mp -= magics[index]->getCost();
	}
	*/
	
	int getAttack();
	int getDiffence();

	void healHp(int delta);
	void healHp();

	void draw_map(int x, int y, int frame, int direction);

	item_ptr setEquipment(ID id, int type);
	item_ptr setEquipment(item_ptr item, int type);

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
	//装備関係の関数　一応残す
	/*
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
	*/

	Equipment getEquipment() { return equipment; }

	item_ptr getEquipment(int type) {
		switch (type) {
		case 1:
			return equipment.weapon;
			break;
		case 2:
			return equipment.shield;
			break;
		case 3:
			return equipment.chest;
			break;
		case 4:
			return equipment.arm;
			break;
		case 5:
			return equipment.head;
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