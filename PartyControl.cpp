#include "PartyControl.h"
#include "WoodSword.h"
#include "Portion.h"

PartyControl::PartyControl() {

}

PartyControl::PartyControl(vector <Player*> players, int num, int coin) {
	this->member = players;
	this->num_MagicStone = num;
	this->coin = coin;
	for (int i = 0; i < 10; i++) {
		this->items.push_back(WoodSword());
		this->items.push_back(Portion());
	}
}

Player* PartyControl::getMember(int index) {
	return this->member[index];
}

int PartyControl::getNumMember() {
	return this->member.size();
}

Item PartyControl::getItem(int index){
	return this->items[index];
}

int PartyControl::getNumItem() {
	return this->items.size();
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