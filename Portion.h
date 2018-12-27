#pragma once
#include "Item.h"
#include "PartyControl.h"

class Portion : public Item {
private:
	int point;

public:
	Portion();
	bool effectBattle();
	bool effectMap();
	void select(PartyControl* pc);
};