#include "Magic.h"
#include "DxLib.h"
#include "IDs.h"


Magic::Magic() :
	name(NULL),
	cost(NULL),
	is_map(NULL),
	id(UNDIFINED),
	point(NULL),
	usable_area(NULL),
	effect_area(NULL),
	type(NON)
{

}

Magic::Magic(ID id, string name, int cost, bool map) :
	name(name),
	cost(cost),
	is_map(map),
	id(id),
	point(NULL),
	usable_area(NULL),
	effect_area(NULL),
	type(NON)
{

}

Magic::Magic(ID id) :
	name(NULL),
	cost(NULL),
	is_map(NULL),
	id(id),
	point(NULL),
	usable_area(NULL),
	effect_area(NULL),
	type(NON)
{
	switch (id) {
	case FIREBALL:
		name = "ファイアーボール";
		cost = 5;
		is_map = false;
		point = 10;
		usable_area = 2;
		effect_area = 11;
		type = FIRE;
		break;
	case HEAL:
		name = "ヒール";
		cost = 2;
		is_map = true;
		point = 20;
		usable_area = 2;
		effect_area = 11;
		type = HEALER;
		break;
	}
}

void Magic::getName(int x, int y) {
	DrawFormatString(x, y, GetColor(0, 0, 0), name.c_str());
}
int Magic::getCost() {
	return cost;
}
bool Magic::getIsMap() {
	return is_map;
}

ID Magic::getID() {
	return id;
}

void Magic::effectBattle() {
	//DrawFormatString(100, 100, GetColor(0, 0, 0), "オーバーライドされていません。");
	switch (id) {
	case FIREBALL:
		break;
	case HEAL:
		break;
	}
}

bool Magic::effectMap(std::shared_ptr<PartyControl> pc) {
	//DrawFormatString(100, 100, GetColor(0, 0, 0), "オーバーライドされていません。");
	if (is_map) {
		return true;
	}
	return false;
}

void Magic::draw_battle() {
	switch (id) {
	case FIREBALL:
		break;
	case HEAL:
		break;
	}
}