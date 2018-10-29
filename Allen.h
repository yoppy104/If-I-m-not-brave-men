#pragma once

#include "Player.h"
#include "Weapon.h"

class Allen :public Player {
private:
	int mp;
public:
	Allen(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon _weapon, int _image, int mp);
	virtual int getMp();
	virtual void plusMp(int);
};