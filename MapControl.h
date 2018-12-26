#pragma once

#include "Map.h"
#include "Player.h"
#include "Menu.h"
#include <vector>

//マップ制御用のクラス。Mapクラスを配列として管理する。
class MapControl {
private:
	double disp_rate;
	int position_player[2];
	int mapsize_w;
	int dispsize_w;
	int mapsize_h;
	int dispsize_h;
	int countFrame;
	int directionPlayer;
	std::vector <std::vector<Map*>> maps;
	Player* allen;
	Event now;
	std::vector<NPC> npcs;
	bool is_move;
	bool is_event;
	bool is_chat;
	bool is_menu;
	int image;
	NPC now_chat;
	Menu menu;

public:
	MapControl();
	MapControl(int width, int height, int x, int y, int map, Player* allen);
	~MapControl();
	int getX();
	int getY();
	void Update();
	void show();
	void createMap();
};