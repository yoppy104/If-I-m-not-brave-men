#pragma once
#include <vector>
#include <memory>
#include "DxLib.h"
#include "Player.h"
#include "Item.h"

typedef std::shared_ptr<Item> item_ptr;
typedef std::shared_ptr<Player> player_ptr;

typedef struct {
	ID id;
	item_ptr instance;
	int num;
} ItemData;

class PartyControl {
private:
	std::vector<player_ptr> member; //�v���C���[�L�����N�^�[
	std::vector<ItemData> items;		//�A�C�e��
	int numMagicStone;		//���΂̑���
	int coin;				//�������̑���

public:
	PartyControl() = default;
	PartyControl(std::vector<player_ptr> players, int num, int coin);

	//�A�N�Z�T
	//player����
	player_ptr getMember(int index) const { return member.at(index); }
	std::vector <player_ptr> getMembers() { return member; }
	int getNumMember() { return member.size(); }

	//���΂̐�
	int getNumMagicStone() { return numMagicStone; }

	//��
	int getNumCoin() { return coin; }	

	//�A�C�e������
	int getNumItem() { return items.size(); }
	ItemData getItem(int index) { return items[index]; }

	//�����o�̑���������֐�
	//�w��̃A�C�e��������
	void delItem(int index);
	//�A�C�e����num�����₷
	void addItem(ID id, int num);
	void addItem(const item_ptr item, int num);
	//�A�C�e����num�����炷
	void reduceItem(int index, int num);
	void addNumMagicStone(int delta);
	void addNumCoin(int delta);
	void setEquipment(int member_index, int item_index);
	void replaceEquipment(int member_index, int type);

	void useItemMap(int index);
};