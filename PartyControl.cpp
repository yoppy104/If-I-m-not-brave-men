#include "PartyControl.h"

PartyControl::PartyControl() {

}

PartyControl::PartyControl(vector <Player*> players, int num) {
	this->member = players;
	this->num_MagicStone = num;
}

Player* PartyControl::getMember(int index) {
	return this->member[index];
}

Item PartyControl::getItem(int index){
	return this->items[index];
}

int PartyControl::getNumItem() {
	return this->items.size();
}