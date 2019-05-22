#pragma once
#include "NPC.h"
#include "Item.h"
#include "IDs.h"
#include <vector>
#include "PartyControl.h"
#include <string>

using namespace std;

class Cleark : public NPC {
private:
	typedef struct {
		int window;
		int subWindow;
		int pointer;
	} Image;

	typedef struct {
		int enter;
		int error;
		int move;
		int coin;
		int cancel;
	} Sound;

	vector <ID> items;
	vector <Item> itemsInf;

	int start;

	int select_main;
	int select_sub;
	int select_sell;

	int num;

	std::shared_ptr<PartyControl> pc;

	Image image;

	Sound sound;

public:
	Cleark() = default;
	Cleark(string name, int x, int y, vector<ID> item, vector<string> text, std::shared_ptr<PartyControl> pc);
	int update();
	int sell(); //プレイヤーが売る
	int buy(); //プレイヤーが買う
	bool chat();
};