#include "Imitia.h"
#include "Weapon.h"

Imitia::Imitia(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon _weapon, int _image) :Player(name, x, y, hp, attack, diffence, magic_power, dex, _weapon, _image){
	this->setHasMp(false);
	this->magicstone = 4;
}


int Imitia::getMagicStone() {
	return this->magicstone;
}

void Imitia::plusMagicStone(int delta) {
	this->magicstone += delta;
}