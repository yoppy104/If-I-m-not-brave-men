#include <string.h>
#include "Allen.h"
#include "Weapon.h"

Allen::Allen(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon _weapon, int _image, int mp, int image_dead) :Player(name, x, y, hp, attack, diffence, magic_power, dex, _weapon, _image, image_dead){
	this->mp = mp;
	this->setHasMp(true);
}

int Allen::getMp() {
	return this->mp;
}

void Allen::plusMp(int point) {
	this->mp += point;
}