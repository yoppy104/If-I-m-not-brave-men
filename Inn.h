#pragma once
#include "NPC.h"
#include "PartyControl.h"

class Inn : public NPC {
private:
	int price;
	PartyControl* pc;
	int subwindow_image;
	bool select_main;

public:
	Inn(int pos_x, int pos_y, char name[], vector <char*> text, int price, PartyControl* pc);
	bool chat();
};