#pragma once
#include "Character.h"

class Player;

typedef unsigned long long stagedata;

class Enemy :public Character// �G�̍\����
{
private:

public:
	Enemy(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, int image, int image_dead); //���O,x,y,hp,�U����,�h���,����,�q��

	virtual bool move(int dx, int dy, Player** p, int size_p, Enemy** e, int size_e, stagedata stage);
	virtual void battle(int x, int y, Player** players, int size_players);
};