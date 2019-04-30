#include "PartyControl.h"
#include "Items.h"
#include "DxLib.h"

PartyControl::PartyControl() {

}

PartyControl::PartyControl(vector <shared_ptr<Player>> players, int num, int coin) :
	member(players),
	numMagicStone(num),
	coin(coin)
{
	shared_ptr<Weapon> w(new WoodSword());
	shared_ptr<Item> p(new Portion());
	shared_ptr<Armor> a(new LeatherArm());
	shared_ptr<Armor> s(new LeatherSheild());
	shared_ptr<Armor> c(new LeatherCap());
	shared_ptr<Armor> ch(new LeatherChest());
	for (int i = 0; i < 1; i++) {
		this->items.push_back(w);
		this->items.push_back(p);
		this->items.push_back(a);
		this->items.push_back(s);
		this->items.push_back(c);
		this->items.push_back(ch);
	}
}

PartyControl::~PartyControl() {
	this->items.clear();
}

void PartyControl::delItem(int index) {
	this->items.erase(this->items.begin() + index);
}

void PartyControl::addItem(shared_ptr<Item> item) {
	this->items.push_back(item);
}

void PartyControl::addNumMagicStone(int delta) {
	this->numMagicStone += delta;
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
		//this->member[member_index]->setEquipment(items[item_index]);
	}
	else {
		if (this->member[member_index]->getArmor(temp)->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getArmor(temp));
		}
		//->member[member_index]->setEquipment((Armor*)this->items[item_index], temp);
	}
	this->items.erase(this->items.begin() + item_index);
}

void PartyControl::replaceEquipment(int member_index, int type) {
	shared_ptr<Weapon> nonw(new NonWeapon());
	shared_ptr<Armor> nons(new NonShield());
	shared_ptr<Armor> nona(new NonArm());
	shared_ptr<Armor> nonh(new NonShield());
	shared_ptr<Armor> nonc(new NonChest());

	switch (type) {
	case 1:
		if (this->member[member_index]->getWeapon()->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getWeapon());
		}
		this->member[member_index]->setEquipment(nonw);
		break;
	case 2:
		if (this->member[member_index]->getArmor(2)->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getArmor(2));
		}
		this->member[member_index]->setEquipment(nons, 2);
		break;
	case 3:
		if (this->member[member_index]->getArmor(3)->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getArmor(3));
		}
		this->member[member_index]->setEquipment(nonc, 3);
		break;
	case 4:
		if (this->member[member_index]->getArmor(4)->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getArmor(4));
		}
		this->member[member_index]->setEquipment(nona, 4);
		break;
	case 5:
		if (this->member[member_index]->getArmor(5)->getId() != NOTEQUIPMENT) {
			this->items.push_back(this->member[member_index]->getArmor(5));
		}
		this->member[member_index]->setEquipment(nonh, 5);
		break;
	}
}