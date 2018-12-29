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

public:
	Cleark();
	Cleark(char name[], int x, int y, vector<Item*> item, vector<char*> text, PartyControl* pc);
	int update();
	int sell(); //プレイヤーが売る
	int buy(); //プレイヤーが買う
	bool chat();
};