#include "Weapon.h"

Weapon::Weapon() {
	 
}

Weapon::Weapon(char name[], int id, bool is_sell, int point, int price, int weight, int sound, int image):Item(name, id, price, is_sell, image, 1) {
	this->point = point;
	this->weight = weight;
	this->sound = sound;
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