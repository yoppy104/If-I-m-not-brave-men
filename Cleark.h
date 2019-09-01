#pragma once
#include "Npc.h"
#include "Item.h"
#include "IDs.h"
#include <vector>
#include "PartyControll.h"
#include <string>

/*
概要 :	店員用のクラス。
		武器屋、防具屋、道具屋は区別しない
*/

class Cleark : public NPC {
private:
	using Image = struct {
		int window;
		int subWindow;
		int pointer;
	};

	using Sound = struct {
		int enter;
		int error;
		int move;
		int coin;
		int cancel;
	};

	std::vector <ID> items;			//アイテムのID。実際に受け渡すもの
	std::vector <Item> itemsInf;	//アイテムの情報を出力するためのもの

	int start;

	int select_main;	//主選択
	int select_sub;		//はい、いいえの選択
	int select_sell;	//売却するときのアイテム選択カーソル

	bool is_buy;

	bool is_select_value;
	int selected_value;

	std::shared_ptr<PartyControll> pc;

	Image image;

	Sound sound;

public:
	Cleark() = default;
	Cleark(std::string name, int x, int y, std::vector<ID> item, std::vector<std::string> text, std::shared_ptr<PartyControll> pc);
	int update();
	int sell(); //プレイヤーが売る
	int buy(); //プレイヤーが買う
	bool chat();

	bool SelectValue(int max_value);
};