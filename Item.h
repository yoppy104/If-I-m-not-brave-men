#pragma once

#include <string>
#include "IDs.h"



typedef struct {
	int buy;
	int sell;
} Price;

typedef struct {
	bool weapon;
	bool shield;
	bool arm;
	bool head;
	bool chest;
} IsEquip;

class Item {
protected:
	std::string name;
	ID id;			//id
	Price price;
	bool isSell;	//���p�\���ǂ���
	int image;		//�摜
	IsEquip isEquip;

	/*
	���ꂼ��̃A�C�e���ł̐��l���Ǘ�����ϐ�:point
	����F�U����
	�h��F�h���
	���Օi�F�񕜗ʂ�㏸��
	*/
	int point;

public:
	Item() = default;
	Item(std::string name, ID id, int price, bool is_sell, int image, int is_equip);
	Item(ID id);
	ID getId() { return id; }
	int getPriceBuy() { return price.buy; }
	int getPriceSell() { return price.sell; }
	bool getIsSell() { return isSell; }
	void getName(int x, int y);
	int getImage() { return image; }
	int getIsEquip();
	bool effectBattle();
	bool effectMap();
	int getPoint() { return point; }

	/*
	����̏ꍇ�Ɏg�p����֐�
	*/
	void drawAttackableArea(); //�U���\�G���A��`��
	void selectAttack(); //�U���͈͂�I��
	void drawAnimation(); //�U���A�j���[�V������`��
};