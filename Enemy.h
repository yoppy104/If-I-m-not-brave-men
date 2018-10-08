#pragma once
#include "Character.h"

class Player;

typedef unsigned long long stagedata;

class Enemy :public Character// “G‚Ì\‘¢‘Ì
{
private:
	int image; // ‰æ‘œ

public:
	Enemy(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, int image); //–¼‘O,x,y,hp,UŒ‚—Í,–hŒä—Í,–‚—Í,•q·

	void move(Player* p, Enemy* e, int background_image, stagedata stage);

	int getImage();
};