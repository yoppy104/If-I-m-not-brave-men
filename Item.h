#pragma once

#include <string>
#include <memory>
#include "IDs.h"

class Player;

/*
�T�v :	�A�C�e���N���X
		�����N���X�͂�����p������B
*/

//���i
using Price = struct {
	int buy;
	int sell;
};

//�����\���ǂ������܂Ƃ߂����́B
using IsEquip = struct {
	bool weapon;
	bool shield;
	bool arm;
	bool head;
	bool chest;
};

class Item {
private:
	std::string name;
	ID id;			//id
	Price price;	//�l�i
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

	int attack_length;

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
	bool effectMap(std::shared_ptr<Player> player);
	int getPoint() { return point; }
	int getAttackLength() { return attack_length; }

	/*
	����̏ꍇ�Ɏg�p����֐�
	*/
	void drawAttackableArea(); //�U���\�G���A��`��
	void selectAttack(); //�U���͈͂�I��
	void drawAnimation(); //�U���A�j���[�V������`��
};