#include "Craig.h"
#include "Weapon.h"
#include "IDs.h"

Craig::Craig(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon* _weapon, Armor* head, Armor* arm, Armor* chest, Armor* shield, int _image, int image_dead) :Player(name, x, y, hp, attack, diffence, magic_power, dex, _weapon, head, arm, chest, shield, _image, image_dead) {
	this->setHasMp(false);
	this->id = CRAIG;
	this->magicstone = 0;
}


int Craig::getMagicStone() {
	return this->magicstone;
}

void Craig::plusMagicStone(int delta) {
	this->magicstone += delta;
}