#include "Weapon.h"

Weapon::Weapon() {
	 
}

Weapon::Weapon(int point, int price, int weight, int attackable, int attack_area) {
	this->point = point;
	this->price = price;
	this->weight = weight;
	this->attackable = attackable;
	this->attack_area = attack_area;
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