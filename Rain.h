#pragma once
#include "Player.h"
#include "Weapon.h"

class Rain :public Player {
private:
	int magicstone;
public:
	Rain(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon _weapon, int _image, int image_dead);

	virtual int getMagicStone();
	virtual void plusMagicStone(int);
};