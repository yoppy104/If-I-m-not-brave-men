#pragma once

#include "Item.h"

class Armor : public Item {
protected:
	int point; // �ϓ�����l
	int weight; // �d�ʁB����ɂ���đ����ł����肪�ς��B�̌��łł͎������Ȃ�

public:
	Armor();
	Armor(char name[], int id, bool is_sell, int point, int price, int weight, int image, int part);
	int getPoint();
	int getWeight();

};