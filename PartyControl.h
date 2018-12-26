#pragma once
#include <vector>
#include "Player.h"
#include "Item.h"

using namespace std;

class PartyControl {
private:
	vector<Player*> member;
	vector<Item> items;
	int num_MagicStone;

public:
	PartyControl();
	PartyControl(vector<Player*> players, int num);
	Player* getMember(int index);
	Item getItem(int index);
	int getNumItem();
};