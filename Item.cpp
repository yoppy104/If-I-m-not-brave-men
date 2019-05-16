#include "Item.h"
#include <string>
#include "DxLib.h"
#include "IDs.h"

Item::Item(string name, ID id, int price, bool is_sell, int image, int is_equip):
	name(name),
	id(id),
	price{price, (int)price / 2},
	isSell(is_sell),
	image(image),
	isEquip{false, false, false, false}
{
	switch (is_equip)
	{
	case 1:
		isEquip.weapon = true;
		break;
	case 2:
		isEquip.shield = true;
		break;
	case 3:
		isEquip.chest = true;
		break;
	case 4:
		isEquip.arm = true;
		break;
	case 5:
		isEquip.head = true;
	default:
		break;
	}
}

Item::Item(ID id) :
	name("NULL"),
	id(id),
	price{0, 0},
	isSell(true),
	image(0),
	isEquip{false, false, false, false}
{
	switch (id) {
	case WOODSWORD:
		name = "ñÿåï";
		price.buy = 100;
		price.sell = price.buy / 2;
		point = 5;
		image = 0;
		isEquip.weapon = true;
		break;
	case STONESWORD:
		name = "êŒÇÃåï";
		price.buy = 300;
		price.sell = price.buy / 2;
		point = 7;
		image = 0;
		isEquip.weapon = true;
		break;
	case STEALSWORD:
		name = "ìSÇÃåï";
		price.buy = 1000;
		price.sell = price.buy / 2;
		point = 11;
		image = 0;
		isEquip.weapon = true;
		break;
	case NOTEQUIPMENT:
		name = "ñ¢ëïîı";
		isSell = false;
		point = 0;
		isEquip.weapon = true;
		isEquip.arm = true;
		isEquip.head = true;
		isEquip.chest = true;
		isEquip.shield = true;
		break;
	case LEATHERARM:
		name = "îÁÇÃ‚ƒéË";
		price.buy = 300;
		price.sell = price.buy / 2;
		point = 2;
		image = 0;
		isEquip.arm = true;
		break;
	case LEATHERCAP:
		name = "îÁÇÃñXéq";
		price.buy = 400;
		price.sell = price.buy / 2;
		point = 5;
		image = 0;
		isEquip.head = true;
		break;
	case LEATHERCHEST:
		name = "îÁÇÃãπìñÇƒ";
		price.buy = 600;
		price.sell = price.buy / 2;
		point = 6;
		image = 0;
		isEquip.chest = true;
		break;
	case LEATHERSHIELD:
		name = "îÁÇÃèÇ";
		price.buy = 500;
		price.sell = price.buy / 2;
		point = 5;
		image = 0;
		isEquip.shield = true;
		break;
	case PORTION:
		name = "âÒïúñÚ";
		price.buy = 100;
		price.sell = price.buy / 2;
		point = 20;
		image = 0;
		break;
	default:
		break;
	}
}

void Item::getName(int x, int y) {
	DrawFormatString(x, y, GetColor(0, 0, 0), name.c_str());
}

bool Item::effectBattle() {
	return false;
}

int Item::getIsEquip() {
	if (isEquip.arm) {
		return 4;
	}
	else if (isEquip.head) {
		return 5;
	}
	else if (isEquip.chest) {
		return 3;
	}
	else if (isEquip.shield) {
		return 2;
	}
	else if (isEquip.weapon) {
		return 1;
	}
	return 0;
}

bool Item::effectMap() {
	return false;
}

void Item::drawAttackableArea() {

}

void Item::selectAttack() {

}

void Item::drawAnimation() {

}