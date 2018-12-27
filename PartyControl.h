#pragma once
#include <vector>
#include "Player.h"
#include "Item.h"

using namespace std;

class PartyControl {
private:
	vector<Player*> member; //�v���C���[�L�����N�^�[
	vector<Item> items;		//�A�C�e��
	int num_MagicStone;		//���΂̑���
	int coin;				//�������̑���

public:
	PartyControl();
	PartyControl(vector<Player*> players, int num, int coin);
	Player* getMember(int index);
	int getNumMember();
	Item getItem(int index);
	int getNumItem();
	void delItem(int index);
	int getNumMagicStone();
	int getNumCoin();
	void addNumMagicStone(int delta);
	void addNumCoin(int delta);
};