#pragma once
#include <vector>
#include <memory>
#include "DxLib.h"
#include "Item.h"
#include "Player.h"


using namespace std;


typedef struct {
	ID id;
	std::shared_ptr<Item> instance;
	int num;
} ItemData;

class PartyControl {
private:
	vector<std::shared_ptr<Player>> member; //�v���C���[�L�����N�^�[
	vector<ItemData> items;		//�A�C�e��
	int numMagicStone;		//���΂̑���
	int coin;				//�������̑���

public:
	PartyControl() = default;
	PartyControl(vector<std::shared_ptr<Player>> players, int num, int coin);

	//�A�N�Z�T
	//player����
	std::shared_ptr<Player> getMember(int index) { return member[index]; }
	vector <std::shared_ptr<Player>> getMembers() { return member; }
	int getNumMember() { return member.size(); }

	//���΂̐�
	int getNumMagicStone() { return numMagicStone; }

	//��
	int getNumCoin() { return coin; }	

	//�A�C�e������
	int getNumItem() { return items.size(); }
	ItemData getItem(int index) { return items[index]; }
	shared_ptr<Item> getItemInstance(int index) { return items[index].instance; }

	//�����o�̑���������֐�
	//�w��̃A�C�e��������
	void delItem(int index);
	//�A�C�e����num�����₷
	void addItem(ID id, int num);
	//�A�C�e����num�����炷
	void reduceItem(int index, int num);
	void addNumMagicStone(int delta);
	void addNumCoin(int delta);
	void setEquipment(int member_index, int item_index);
	void replaceEquipment(int member_index, int type);

	void useItemMap(int index);
};