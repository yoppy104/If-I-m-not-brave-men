#pragma once

#include "Player.h"
#include "Weapon.h"

class Craig :public Player {
private:
public:
	Craig(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon _weapon, int _image);
};