#pragma once
#include "NPC.h"
#include "Item.h"
#include "IDs.h"
#include <vector>
#include "PartyControl.h"
#include <string>



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

	std::vector <ID> items;
	std::vector <Item> itemsInf;

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
	Cleark(std::string name, int x, int y, std::vector<ID> item, std::vector<std::string> text, std::shared_ptr<PartyControl> pc);
	int update();
	int sell(); //プレイヤーが売る
	int buy(); //プレイヤーが買う
	bool chat();
};