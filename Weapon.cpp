#include "Weapon.h"
#include <math.h>
#include "IDs.h"

Weapon::Weapon() {
	 
}

Weapon::Weapon(char name[], int id, bool is_sell, int point, int price, int weight, int sound, int image):Item(name, id, price, is_sell, image, 1) {
	this->point = point;
	this->weight = weight;
	this->sound = sound;
}

Weapon::Weapon(int id) :
	Item(id),
	point(NULL),
	weight(NULL),
	sound(NULL)
{
	switch (this->id)
	{
	case NOTEQUIPMENT:
		point = 0;
		weight = 0;
		sound = 0;
		break;
	case WOODSWORD:
		point = 5;
		weight = 1;
		sound = 0;
		break;
	default:
		break;
	}
}

int Weapon::getPoint() {
	return this->point;
}

int Weapon::getSound() {
	return this->sound;
}

void Weapon::drawAttackableArea() {

}

void Weapon::selectAttack() {

}

void Weapon::drawAnimation() {

}

bool Weapon::effectBattle(){
	return false;
}

bool Weapon::effectMap() {
	return false;
}