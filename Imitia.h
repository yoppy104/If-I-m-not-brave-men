#pragma once

#include "Player.h"
#include "Weapon.h"

class Imitia :public Player {
private:
	int magicstone;

public:
	Imitia(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon* _weapon, Armor* head, Armor* arm, Armor* chest, Armor* shield, int _image, int image_dead);

	virtual int getMagicStone();
	virtual void plusMagicStone(int);
};
