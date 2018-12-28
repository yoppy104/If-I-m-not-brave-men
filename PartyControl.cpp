#include "PartyControl.h"
#include "Items.h"
#include "DxLib.h"

PartyControl::PartyControl() {

}

PartyControl::PartyControl(vector <Player*> players, int num, int coin) {
	this->member = players;
	this->num_MagicStone = num;
	this->coin = coin;
	for (int i = 0; i < 3; i++) {
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
		this->items.push_back(this->member[member_index]->getWeapon());
		this->member[member_index]->setEquipment((Weapon*)this->items[item_index]);
	}
	else {
		this->items.push_back(this->member[member_index]->getArmor(temp));
		this->member[member_index]->setEquipment((Armor*)this->items[item_index], temp);
	}
	this->items.erase(this->items.begin() + item_index);
}