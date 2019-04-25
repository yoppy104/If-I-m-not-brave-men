#include "PartyControl.h"
#include "Items.h"
#include "DxLib.h"

PartyControl::PartyControl() {

}

PartyControl::PartyControl(vector <Player*> players, int num, int coin) {
	this->member = players;
	this->num_MagicStone = num;
	this->coin = coin;
	for (int i = 0; i < 1; i++) {
		this->items.push_back(new WoodSword());
		this->items.push_back(new Portion());
		this->items.push_back(new LeatherArm());
		this->items.push_back(new LeatherSheild());
		this->items.push_back(new LeatherCap());
		this->items.push_back(new LeatherChest());
	}

	this->items[0]->getName(400, 450);
	WaitTimer(500);
}

PartyControl::~PartyControl() {
	this->items.clear();
}

Player* PartyControl::getMember(int index) {
	return this->member[index];
}

int PartyControl::getNumMember() {
	return this->member.size();
}

Item* PartyControl::getItem(int index){
	return this->items[index];
}

int PartyControl::getNumItem() {
	return this->items.size();
}

void PartyControl::delItem(int index) {
	this->items.erase(this->items.begin() + index);
}

void PartyControl::addItem(Item* item) {
	this->items.push_back(item);
}

int PartyControl::getNumMagicStone() {
	return this->num_MagicStone;
}

int PartyControl::getNumCoin() {
	return this->coin;
}

void PartyControl::addNumMagicStone(int delta) {
	this->num_MagicStone += delta;
}

void PartyControl::addNumCoin(int delta) {
	this->coin += delta;
}


void PartyControl::setEquipment(int member_index, int item_index) {
	int temp = this->items[item_index]->getIsEquip();
	if (temp == 1) {
		if (this->member[member_index]->getWeapon()->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getWeapon());
		}
		this->member[member_index]->setEquipment((Weapon*)this->items[item_index]);
	}
	else {
		if (this->member[member_index]->getArmor(temp)->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getArmor(temp));
		}
		this->member[member_index]->setEquipment((Armor*)this->items[item_index], temp);
	}
	this->items.erase(this->items.begin() + item_index);
}

void PartyControl::replaceEquipment(int member_index, int type) {
	switch (type) {
	case 1:
		if (this->member[member_index]->getWeapon()->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getWeapon());
		}
		this->member[member_index]->setEquipment(new NonWeapon());
		break;
	case 2:
		if (this->member[member_index]->getWeapon()->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getArmor(2));
		}
		this->member[member_index]->setEquipment(new NonShield(), 2);
		break;
	case 3:
		if (this->member[member_index]->getWeapon()->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getArmor(3));
		}
		this->member[member_index]->setEquipment(new NonChest(), 3);
		break;
	case 4:
		if (this->member[member_index]->getWeapon()->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getArmor(4));
		}
		this->member[member_index]->setEquipment(new NonArm(), 4);
		break;
	case 5:
		if (this->member[member_index]->getWeapon()->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getArmor(5));
		}
		this->member[member_index]->setEquipment(new NonHead(), 5);
		break;
	}
}

vector <Player*> PartyControl::getMembers() {
	return this->member;
}

int* PartyControl::getCoin() {
	return &this->coin;
}

vector <Item*> PartyControl::getItems() {
	return this->items;
}