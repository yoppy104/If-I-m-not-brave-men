#pragma once

#include "Map.h"
#include "Player.h"
#include "Menu.h"
#include <vector>

class Player;
class Map;

//�v���C���[�̌����Ă������
enum DirectionPlayer {
	FRONT,
	BACK,
	RIGHT,
	LEFT
};

//�}�b�v����p�̃N���X�BMap�N���X��z��Ƃ��ĊǗ�����B
class MapControl {
private:

	//����
	typedef struct {
		int main;
		int walk;
		int error;
		int enter;
	} Sound;

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