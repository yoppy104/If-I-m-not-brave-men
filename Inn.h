#pragma once
#include "Npc.h"
#include "PartyControll.h"

/*
概要 :	宿屋のクラス
*/

class Inn : public NPC {
private:
	using Sound = struct {
		int enter;
		int error;
		int move;
		int cancel;
		int coin;
		int heal;
		int yado;
	};

	int price;	//宿泊費
	std::shared_ptr<PartyControll> pc;
	int subwindow_image;	//はい、いいえの項目を表示するウィンドウ
	bool select_main;		//はい、いいえを選択するカーソル
	int fade;

	Sound sounds;

public:
	Inn(int pos_x, int pos_y, char name[], std::vector <std::string> text, int price, std::shared_ptr<PartyControll> pc);
	bool chat();
};