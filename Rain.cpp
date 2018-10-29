#include "Rain.h"
#include "Weapon.h"

Rain::Rain(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon _weapon, int _image) :Player(name, x, y, hp, attack, diffence, magic_power, dex, _weapon, _image) {
	this->setHasMp(false);
	this->magicstone = 10;
}


int Rain::getMagicStone() {
	return this->magicstone;
}

void Rain::plusMagicStone(int delta) {
	this->magicstone += delta;
}
