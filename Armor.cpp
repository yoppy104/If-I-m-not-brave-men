#include "Armor.h"

Armor::Armor(char name[], int id, bool is_sell, int point, int price, int weight, int image, int part) :Item(name, id, price, is_sell, image, part) {
	this->point = point;
	this->weight = weight;
}

int Armor::getPoint() {
	return this->point;
}

int Armor::getWeight() {
	return this->weight;
}