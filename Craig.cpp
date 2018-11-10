#include "Craig.h"
#include "Weapon.h"

Craig::Craig(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon _weapon, int _image, int image_dead) :Player(name, x, y, hp, attack, diffence, magic_power, dex, _weapon, _image, image_dead) {
	this->setHasMp(false);
	this->magicstone = 0;
}


int Craig::getMagicStone() {
	return this->magicstone;
}

void Craig::plusMagicStone(int delta) {
	this->magicstone += delta;
}