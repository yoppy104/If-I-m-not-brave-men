#pragma once
#include "Character.h"

class Player;

typedef unsigned long long stagedata;

class Enemy :public Character// �G�̍\����
{
private:

public:
	Enemy(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, int image); //���O,x,y,hp,�U����,�h���,����,�q��

	void move(Player* p, Enemy* e, int background_image, stagedata stage);
};