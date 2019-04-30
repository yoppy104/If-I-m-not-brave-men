#pragma once

#include "Map.h"
#include "Player.h"
#include "Menu.h"
#include <vector>

class Player;
class Map;

//マップサイズ
typedef struct {
	int width;
	int height;
} MapSize;

//ディスプレイサイズ
typedef struct {
	int width;
	int height;
} DispSize;

//プレイヤーの向いている方向
enum DirectionPlayer {
	FRONT,
	BACK,
	RIGHT,
	LEFT
};

//音声
typedef struct {
	int main;
	int walk;
	int error;
	int enter;
} Sound;

//マップ制御用のクラス。Mapクラスを配列として管理する。
class MapControl {
private:
	double dispRate;
	Vector positionPlayer;
	DirectionPlayer directionPlayer;
	MapSize mapSize;
	DispSize dispSize;
	int countFrame;
	std::vector <std::vector<shared_ptr<Map>>> maps;
	shared_ptr<Player> allen;
	shared_ptr<Event> now;
	std::vector<shared_ptr<NPC>> npcs;
	bool isMove;
	bool isEvent;
	bool isChat;
	bool isMenu;
	int image;
	shared_ptr<NPC> nowChat;
	shared_ptr<Menu> menu;
	shared_ptr<PartyControl> pc;

	Sound sounds;

public:
	MapControl();
	MapControl(int width, int height, int x, int y, int map, const shared_ptr<Player> allen, const shared_ptr<PartyControl> pc);
	~MapControl();
	int getX() const { positionPlayer.x; }
	int getY() const { positionPlayer.y; }
	int Update();
	void show();
	void createMap();
};