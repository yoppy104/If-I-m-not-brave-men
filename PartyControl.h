#pragma once
#include <vector>
#include "Player.h"
#include "Item.h"

using namespace std;

class PartyControl {
private:
	vector<Player*> member; //プレイヤーキャラクター
	vector<Item*> items;		//アイテム
	int num_MagicStone;		//魔石の総数
	int coin;				//所持金の総数

public:
	PartyControl();
	PartyControl(vector<Player*> players, int num, int coin);
	~PartyControl();
	Player* getMember(int index);
	int getNumMember();
	Item* getItem(int index);
	int getNumItem();
	void delItem(int index);
	void addItem(Item* item);
	int getNumMagicStone();
	int getNumCoin();
	void addNumMagicStone(int delta);
	void addNumCoin(int delta);
	void setEquipment(int member_index, int item_index);
	void replaceEquipment(int member_index, int type);
};