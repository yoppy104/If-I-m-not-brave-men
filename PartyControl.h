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
	vector<std::shared_ptr<Player>> member; //プレイヤーキャラクター
	vector<ItemData> items;		//アイテム
	int numMagicStone;		//魔石の総数
	int coin;				//所持金の総数

public:
	PartyControl() = default;
	PartyControl(vector<std::shared_ptr<Player>> players, int num, int coin);

	//アクセサ
	//player周り
	std::shared_ptr<Player> getMember(int index) { return member[index]; }
	vector <std::shared_ptr<Player>> getMembers() { return member; }
	int getNumMember() { return member.size(); }

	//魔石の数
	int getNumMagicStone() { return numMagicStone; }

	//金
	int getNumCoin() { return coin; }	

	//アイテム周り
	int getNumItem() { return items.size(); }
	ItemData getItem(int index) { return items[index]; }
	shared_ptr<Item> getItemInstance(int index) { return items[index].instance; }

	//メンバの増減をする関数
	//指定のアイテムを消す
	void delItem(int index);
	//アイテムをnum個分増やす
	void addItem(ID id, int num);
	//アイテムをnum個分減らす
	void reduceItem(int index, int num);
	void addNumMagicStone(int delta);
	void addNumCoin(int delta);
	void setEquipment(int member_index, int item_index);
	void replaceEquipment(int member_index, int type);

	void useItemMap(int index);
};