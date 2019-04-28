#pragma once
#include "NPC.h"
#include "PartyControl.h"

class Inn : public NPC {
private:
	int price;
	PartyControl* pc;
	int subwindow_image;
	bool select_main;
	int fade;

	int sound_enter;
	int sound_error;
	int sound_move;
	int sound_cancel;
	int sound_coin;
	int sound_heal;
	int sound_yado;

public:
	Inn(int pos_x, int pos_y, char name[], vector <string> text, int price, PartyControl* pc);
	bool chat();
};