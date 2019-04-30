#pragma once
#include <vector>
#include "Player.h"
#include "Item.h"

using namespace std;

class Player;
class Magic;

class PartyControl {
private:
	vector<shared_ptr<Player>> member; //プレイヤーキャラクター
	vector<shared_ptr<Item>> items;		//アイテム
	int numMagicStone;		//魔石の総数
	int coin;				//所持金の総数

public:
	PartyControl();
	PartyControl(vector<shared_ptr<Player>> players, int num, int coin);
	~PartyControl();
	shared_ptr<Player> getMember(int index) { return member[index]; }
	int getNumMember() { return member.size(); }
	shared_ptr<Item> getItem(int index) { return items[index]; }
	int getNumItem() { return items.size(); }
	void delItem(int index);
	void addItem(shared_ptr<Item> item);
	int getNumMagicStone() { return numMagicStone; }
	int getNumCoin() { return coin; }
	void addNumMagicStone(int delta);
	void addNumCoin(int delta);
	void setEquipment(int member_index, int item_index);
	void replaceEquipment(int member_index, int type);
	vector <shared_ptr<Player>> getMembers() { return member; }
	vector <shared_ptr<Item>> getItems() { return items; }
};