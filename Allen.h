#pragma once

#include "Player.h"
#include "Weapon.h"

class Allen :public Player {
private:
	int mp;
public:
	Allen(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon* _weapon, Armor* head, Armor* arm, Armor* chest, Armor* shield, int _image, int mp, int image_dead);
	virtual int getMp();
	virtual void plusMp(int);
};