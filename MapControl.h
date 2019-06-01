#pragma once

#include "Map.h"
#include "Player.h"
#include "Menu.h"
#include <vector>

class Player;
class Map;

//プレイヤーの向いている方向
enum DirectionPlayer {
	FRONT,
	BACK,
	RIGHT,
	LEFT
};

//マップ制御用のクラス。Mapクラスを配列として管理する。
class MapControl {
private:

	//音声
	typedef struct {
		int main;
		int walk;
		int error;
		int enter;
	} Sound;

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

	double dispRate;
	Vector positionPlayer;
	DirectionPlayer directionPlayer;
	MapSize mapSize;
	DispSize dispSize;
	int countFrame;
	std::vector <std::vector<std::shared_ptr<Map>>> maps;
	std::shared_ptr<Player> allen;
	std::shared_ptr<Event> now;
	std::vector<std::shared_ptr<NPC>> npcs;
	bool isMove;
	bool isEvent;
	bool isChat;
	bool isMenu;
	int image;
	std::shared_ptr<NPC> nowChat;
	std::shared_ptr<Menu> menu;
	std::shared_ptr<PartyControl> pc;

	Sound sounds;

public:
	MapControl() = default;
	MapControl(int width, int height, int x, int y, int map, std::shared_ptr<Player> allen, std::shared_ptr<PartyControl> pc);
	~MapControl();
	int getX() const { positionPlayer.x; }
	int getY() const { positionPlayer.y; }
	int Update();
	void show();
	void createMap();
};