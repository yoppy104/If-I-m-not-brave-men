#include "Item.h"
#include <string>
#include "DxLib.h"

Item::Item() {

}

Item::Item(char name[], int id, int price, bool is_sell, int image, int is_equip) {
	strcpy(this->name, name);
	this->id = id;
	this->price_buy = price;
	this->price_sell = price / 2;
	this->is_sell = is_sell;
	this->image = image;

	this->is_equip_arm = false;
	this->is_equip_chest = false;
	this->is_equip_head = false;
	this->is_equip_shield = false;
	this->is_equip_weapon = false;

	switch (is_equip)
	{
	case 1:
		this->is_equip_weapon = true;
		break;
	case 2:
		this->is_equip_shield = true;
		break;
	case 3:
		this->is_equip_chest = true;
		break;
	case 4:
		this->is_equip_arm = true;
		break;
	case 5:
		this->is_equip_head = true;
	default:
		break;
	}
}

Item::~Item() {

}

int Item::getId() {
	return this->id;
}

bool Item::getIsSell() {
	return this->is_sell;
}

int Item::getPriceBuy() {
	return this->price_buy;
}

int Item::getPriceSell() {
	return this->price_sell;
}

int Item::getImage() {
	return this->image;
}

void Item::getName(int x, int y) {
	DrawFormatString(x, y, GetColor(0, 0, 0), this->name);
}

bool Item::effectBattle() {
	return false;
}

bool Item::effectMap() {
	return false;
}
