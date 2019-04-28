#pragma once
#include "NPC.h"
#include "Items.h"
#include <vector>
#include "PartyControl.h"
#include <string>

using namespace std;

class Cleark : public NPC {
private:
	vector <Item*> items;

	int start;

	int select_main;
	int select_sub;
	int select_sell;

	int num;

	PartyControl* pc;

	int window_image;
	int subwindow_image;
	int pointer_image;

	int sound_enter;
	int sound_error;
	int sound_move;
	int sound_coin;
	int sound_cancel;

public:
	Cleark();
	Cleark(char name[], int x, int y, vector<Item*> item, vector<string> text, PartyControl* pc);
	int update();
	int sell(); //プレイヤーが売る
	int buy(); //プレイヤーが買う
	bool chat();
};