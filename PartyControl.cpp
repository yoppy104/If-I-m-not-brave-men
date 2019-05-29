#include "PartyControl.h"
#include "Item.h"
#include "DxLib.h"

PartyControl::PartyControl(vector <std::shared_ptr<Player>> players, int num, int coin) :
	member(players),
	numMagicStone(num),
	coin(coin)
{
	addItem(WOODSWORD, 1);
	addItem(LEATHERARM, 1);
	addItem(LEATHERCAP, 1);
	addItem(PORTION, 3);
}

void PartyControl::delItem(int index) {
	items.erase(items.begin() + index);
}

void PartyControl::addItem(ID id, int num){
	int i = 0;
	for (i; i < items.size(); i++) {
		if (items[i].id == id) {
			items[i].num++;
			return;
		}
	}
	items.push_back(ItemData{ id, std::make_shared<Item>(Item(id)), 1 });
}

void PartyControl::reduceItem(int index, int num) {
	if (items[index].num >= num) {
		items[index].num -= num;
	}
	else {
		delItem(index);
	}
}

void PartyControl::addNumMagicStone(int delta) {
	numMagicStone += delta;
}

void PartyControl::addNumCoin(int delta) {
	coin += delta;
}


void PartyControl::setEquipment(int member_index, int item_index) {
	/*
	int temp = items[item_index].instance->getIsEquip();
	if (temp == 1) {
		if (member[member_index]->hasEquip(1)) {
			addItem(member[member_index]->getWeaponId(), 1);
		}
		member[member_index]->setEquipment(items[item_index].instance->getId(), 1);
	}
	else {
		if (member[member_index]->hasEquip(temp)) {
			addItem(member[member_index]->getArmorId(temp), 1);
		}
		member[member_index]->setEquipment(items[item_index].instance->getId(), temp);
	}
	items[item_index].num--;
	if (items[item_index].num == 0) {
		items.erase(items.begin() + item_index);
	}
	*/
	int equipType = items[item_index].instance->getIsEquip();
	if (member[member_index]->hasEquip(equipType)) {

	}
}

void PartyControl::replaceEquipment(int member_index, int type) {
	switch (type) {
	case 1:
		if (member[member_index]->hasEquip(1)) {
			addItem(member[member_index]->getWeaponId(), 1);
		}
		member[member_index]->setEquipment(NOTEQUIPMENT, 1);
		break;
	case 2:
		if (member[member_index]->hasEquip(2)) {
			addItem(member[member_index]->getArmorId(2), 1);
		}
		member[member_index]->setEquipment(NOTEQUIPMENT, 2);
		break;
	case 3:
		if (member[member_index]->hasEquip(3)) {
			addItem(member[member_index]->getArmorId(3), 1);
		}
		member[member_index]->setEquipment(NOTEQUIPMENT, 3);
		break;
	case 4:
		if (member[member_index]->hasEquip(4)) {
			addItem(member[member_index]->getArmorId(4), 1);
		}
		member[member_index]->setEquipment(NOTEQUIPMENT, 4);
		break;
	case 5:
		if (member[member_index]->hasEquip(5)) {
			addItem(member[member_index]->getArmorId(5), 1);
		}
		member[member_index]->setEquipment(NOTEQUIPMENT, 5);
		break;
	}
}

void PartyControl::useItemMap(int index) {
	items[index].instance->effectMap();
	items[index].num--;
	if (items[index].num == 0) {
		items.erase(items.begin() + index);
	}
}