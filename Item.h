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
	bool isSell;	//売却可能かどうか
	int image;		//画像
	IsEquip isEquip;

	/*
	それぞれのアイテムでの数値を管理する変数:point
	武器：攻撃力
	防具：防御力
	消耗品：回復量や上昇量
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
	武器の場合に使用する関数
	*/
	void drawAttackableArea(); //攻撃可能エリアを描画
	void selectAttack(); //攻撃範囲を選択
	void drawAnimation(); //攻撃アニメーションを描画
};