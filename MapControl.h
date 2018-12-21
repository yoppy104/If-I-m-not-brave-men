#pragma once

#include "Map.h"
#include "Player.h"
#include <vector>

//�}�b�v����p�̃N���X�BMap�N���X��z��Ƃ��ĊǗ�����B
class MapControl {
private:
	int position_player[2];
	std::vector <std::vector<Map*>> maps;
	int image;

public:
	MapControl(int x, int y, int map);
	int getX();
	int getY();
	void show(int dispsize[], Player* allen);
	void createMap();
};