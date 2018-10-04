#pragma once

#include "Player.h"
#include "Weapon.h"

class Allen :public Player {
private:
	int mp;
public:
	Allen(char _name[], int _hp, int _x, int _y, int _attack, int _diffence, Weapon _weapon, int _image, int dex, int mp);
};