#pragma once

#include "Player.h"
#include "Weapon.h"
#include <fstream>

class Allen :public Player {
private:
	int mp;
	int mp_max;
public:
	Allen(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon* _weapon, Armor* head, Armor* arm, Armor* chest, Armor* shield, int _image, int mp, int image_dead);

	virtual int getMp();
	virtual int getMpMax();
	virtual void plusMp(int);
	virtual void plusMp();
};