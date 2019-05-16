#pragma once
#include <vector>
#include "Player.h"
#include "Item.h"

using namespace std;

class Player;
class Magic;

typedef struct {
	ID id;
	unique_ptr<Item> instance;
	int num;
} ItemData;

class PartyControl {
private:
	vector<shared_ptr<Player>> member; //プレイヤーキャラクター
	vector<ItemData> items;		//アイテム
	int numMagicStone;		//魔石の総数
	int coin;				//所持金の総数

public:
	PartyControl() = default;
	PartyControl(vector<shared_ptr<Player>> players, int num, int coin);
	~PartyControl();
	shared_ptr<Player> getMember(int index) { return member[index]; }
	int getNumMember() { return member.size(); }
	int getNumItem() { return items.size(); }
	void delItem(int index);
	void addItem(ID id, int num);
	int getNumMagicStone() { return numMagicStone; }
	int getNumCoin() { return coin; }
	void addNumMagicStone(int delta);
	void addNumCoin(int delta);
	void setEquipment(int member_index, int item_index);
	void replaceEquipment(int member_index, int type);
	vector <shared_ptr<Player>> getMembers() { return member; }
	void getItemInfo(int index, int x, int y) {
		items[index].instance->getName(x, y);
		DrawFormatString(x+200, y, GetColor(0, 0, 0), "%d個", items[index].num);
	}
	bool getItemInfo(int index) {
		return items[index].instance->getIsSell();
	}
	int getItemInfo(int index, bool isBuy) {
		if (isBuy) {
			return items[index].instance->getPriceBuy();
		}
		else {
			return items[index].instance->getPriceSell();
		}
	}
	int getItemIsEquip(int index) {
		return items[index].instance->getIsEquip();
	}
	int getItemPoint(int index) {
		return items[index].instance->getPoint();
	}

	void useItemMap(int index);
};