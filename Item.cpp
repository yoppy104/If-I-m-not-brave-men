#include "Item.h"
#include <string>
#include "DxLib.h"
#include "IDs.h"

Item::Item() {

}

Item::Item(string name, int id, int price, bool is_sell, int image, int is_equip) {
	this->name = name;
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

Item::Item(int id) :
	name(NULL),
	id(id),
	price_buy(NULL),
	price_sell(NULL),
	is_sell(true),
	image(NULL),
	is_equip_weapon(false),
	is_equip_arm(false),
	is_equip_chest(false),
	is_equip_head(false),
	is_equip_shield(false)
{
	switch (this->id) {
	case WOODSWORD:
		name = "–ØŒ•";
		price_buy = 50;
		price_sell = this->price_buy / 2;
		image = 0;
		is_equip_weapon = true;
	case LEATHERARM:
		name = "”ç‚ÌâÄŽè";
		price_buy = 100;
		price_sell = this->price_buy / 2;
		image = 0;
		is_equip_arm = true;
		break;

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
	DrawFormatString(x, y, GetColor(0, 0, 0), this->name.c_str());
}

bool Item::effectBattle() {
	return false;
}

int Item::getIsEquip() {
	if (this->is_equip_arm) {
		return 4;
	}
	else if (this->is_equip_head) {
		return 5;
	}
	else if (this->is_equip_chest) {
		return 3;
	}
	else if (this->is_equip_shield) {
		return 2;
	}
	else if (this->is_equip_weapon) {
		return 1;
	}
	return 0;
}

bool Item::effectMap() {
	return false;
}

int Item::getPoint() {
	return 0;
}