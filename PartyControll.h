#pragma once
#include <vector>
#include <memory>
#include "DxLib.h"
#include "Player.h"
#include "Item.h"

using item_ptr = std::shared_ptr<Item>;
using player_ptr = std::shared_ptr<Player>;

//アイテム情報のひと塊
using ItemData = struct {
	ID id;
	item_ptr instance;
	int num;
};


/*
概要 :	パーティの情報を一括管理するクラス
*/
class PartyControll {
private:
	std::vector<player_ptr> member; //プレイヤーキャラクター
	std::vector<ItemData> items;		//アイテム
	int numMagicStone;		//魔石の総数
	int coin;				//所持金の総数

public:
	PartyControll() = default;
	PartyControll(std::vector<player_ptr> players, int num, int coin);

	//アクセサ
	//player周り
	player_ptr getMember(int index) const { return member.at(index); }
	std::vector <player_ptr> getMembers() { return member; }
	int getNumMember() { return member.size(); }

	//魔石の数
	int getNumMagicStone() { return numMagicStone; }

	//金
	int getNumCoin() { return coin; }	

	//アイテム周り
	int getNumItem() { return items.size(); }
	ItemData getItem(int index) { return items[index]; }

	//メンバの増減をする関数
	//指定のアイテムを消す
	void delItem(int index);
	//アイテムをnum個分増やす
	void addItem(ID id, int num);
	void addItem(const item_ptr item, int num);
	//アイテムをnum個分減らす
	void reduceItem(int index, int num);
	void addNumMagicStone(int delta);
	void addNumCoin(int delta);
	void setEquipment(int member_index, int item_index);
	void replaceEquipment(int member_index, int type);

	void GetItemName(int index, int x, int y);

	void useItemMap(int index);
};