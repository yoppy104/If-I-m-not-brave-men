#pragma once
#include "Npc.h"
#include "PartyControl.h"



class Inn : public NPC {
private:
	typedef struct {
		int enter;
		int error;
		int move;
		int cancel;
		int coin;
		int heal;
		int yado;
	}Sound;

	int price;
	std::shared_ptr<PartyControl> pc;
	int subwindow_image;
	bool select_main;
	int fade;

	Sound sounds;

public:
	Inn(int pos_x, int pos_y, char name[], std::vector <std::string> text, int price, std::shared_ptr<PartyControl> pc);
	bool chat();
};