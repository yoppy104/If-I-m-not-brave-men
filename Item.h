#pragma once

#include <string>

using namespace std;

class Item {
protected:
	string name;
	int id;			//id
	int price_buy;	//買価
	int price_sell; //売価
	bool is_sell;	//売却可能かどうか
	int image;		//画像
	bool is_equip_weapon;	//武器として装備可能か
	bool is_equip_shield;	//盾として装備可能か
	bool is_equip_arm;		//小手として装備可能か
	bool is_equip_head;		//頭装備として装備可能か
	bool is_equip_chest;	//胸に装備可能か

public:
	Item();
	Item(string name, int id, int price, bool is_sell, int image, int is_equip);
	Item(int id);
	~Item();
	int getId();
	int getPriceBuy();
	int getPriceSell();
	bool getIsSell();
	void getName(int x, int y);
	int getImage();
	int getIsEquip();
	virtual bool effectBattle();
	virtual bool effectMap();
	virtual int getPoint();
};