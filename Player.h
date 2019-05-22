#pragma once

#include "Character.h"
#include <vector>
#include "Item.h"
#include <memory>
#include <array>
#include "Magic.h"
#include "PartyControl.h"

#define FIRST_EXP 0

typedef struct {
	std::unique_ptr<Item> weapon; //����
	std::unique_ptr<Item> arm;	 //�Ď�
	std::unique_ptr<Item> head;	 //��
	std::unique_ptr<Item> chest;	 //������
	std::unique_ptr<Item> shield; //��
} Equipment;

typedef struct {
	int allEXP;		//�S�o���l
	int NextEXP;	//���񃌃x���A�b�v�܂ł̌o���l
	int stuckEXP;	//�ݐόo���l
} EXP;

using namespace std;

class Player :public Character{ // �v���C���[�̍\���́A����������ŊǗ�
protected:
	vector <std::unique_ptr<Magic>> magics;
	int numMagicMap;

	EXP exp;

	int LV;
	int charAniframe;
	int StaWindow;
	int Font;
	bool active;
	bool Block;
	
	Equipment equipment;

	int magicStone; // ���΂̏�����


public:
	Player() = default;
	Player(ID id, int x, int y); // id�ɂ��R���X�g���N�^

	~Player();

	virtual int sendEXp(int EXp);

	int getMagicStone() { return magicStone; }
	void plusMagicStone(int);

	void addMagic(ID id);
	int getNumMagics() { return magics.size(); }

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