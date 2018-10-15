#include <string.h>
#include "Allen.h"
#include "Weapon.h"

Allen::Allen(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon _weapon, int _image, int mp) :Player(name, x, y, hp, attack, diffence, magic_power, dex, _weapon, _image){
	this->mp = mp;
}

int Allen::getMp() {
	return this->mp;
}