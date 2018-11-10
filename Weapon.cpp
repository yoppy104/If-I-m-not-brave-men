#include "Weapon.h"

Weapon::Weapon() {
	 
}

Weapon::Weapon(int point, int price, int weight, int attackable, int attack_area, int sound) {
	this->point = point;
	this->price = price;
	this->weight = weight;
	this->attackable = attackable;
	this->attack_area = attack_area;
	this->sound = sound;
}

int Weapon::getPoint() {
	return this->point;
}

int Weapon::getAttackable() {
	return this->attackable;
}

int Weapon::getAttackArea() {
	return this->attack_area;
}

int Weapon::getSound() {
	return this->sound;
}