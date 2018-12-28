#pragma once

#include "Item.h"

class Armor : public Item {
protected:
	int point; // 変動する値
	int weight; // 重量。これによって装備できたりが変わる。体験版では実装しない

public:
	Armor();
	Armor(char name[], int id, bool is_sell, int point, int price, int weight, int image, int part);
	int getPoint();
	int getWeight();

};