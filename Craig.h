#pragma once

#include "Player.h"
#include "Weapon.h"

class Craig :public Player {
private:
public:
	Craig(char _name[], int _hp, int _x, int _y, int _attack, int _diffence, Weapon _weapon, int _image, int dex);
};