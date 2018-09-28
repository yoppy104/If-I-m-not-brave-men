#include "Equipment.h"

Equipment::Equipment() {

}

Equipment::Equipment(int type, int point, int price, int weight, int attackable, int attack_area) {
	this->type = type;
	this->point = point;
	this->price = price;
	this->weight = weight;
	this->attackable = attackable;
	this->attack_area = attack_area;
}

int Equipment::getAttackable() {
	return this->attackable;
}

int Equipment::getAttackArea() {
	return this->attack_area;
}