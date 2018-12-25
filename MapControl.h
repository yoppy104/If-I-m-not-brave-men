#pragma once

#include "Map.h"
#include "Player.h"
#include <vector>

//�}�b�v����p�̃N���X�BMap�N���X��z��Ƃ��ĊǗ�����B
class MapControl {
private:
	int position_player[2];
	int mapsize_w;
	int mapsize_h;
	int countFrame;
	int directionPlayer;
	std::vector <std::vector<Map*>> maps;
	int image;

public:
	MapControl();
	MapControl(int x, int y, int map);
	~MapControl();
	int getX();
	int getY();
	void Update(int code);
	void show(int width, int height, Player* allen);
	void createMap();
};