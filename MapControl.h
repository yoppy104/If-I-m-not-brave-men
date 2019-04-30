#pragma once

#include "Map.h"
#include "Player.h"
#include "Menu.h"
#include <vector>

class Player;
class Map;

//�}�b�v�T�C�Y
typedef struct {
	int width;
	int height;
} MapSize;

//�f�B�X�v���C�T�C�Y
typedef struct {
	int width;
	int height;
} DispSize;

//�v���C���[�̌����Ă������
enum DirectionPlayer {
	FRONT,
	BACK,
	RIGHT,
	LEFT
};

//����
typedef struct {
	int main;
	int walk;
	int error;
	int enter;
} Sound;

//�}�b�v����p�̃N���X�BMap�N���X��z��Ƃ��ĊǗ�����B
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