#include "Magic.h"
#include "DxLib.h"
#include <string.h>

Magic::Magic() {

}

Magic::Magic(int id, char* name, int cost, bool map) {
	strcpy(this->name, name);
	this->cost = cost;
	this->is_map = map;
	this->id = id;
}

void Magic::effectpoint() {

}

void Magic::getName(int x, int y) {
	DrawFormatString(x, y, GetColor(0, 0, 0), this->name);
}
int Magic::getCost() {
	return this->cost;
}
bool Magic::getIsMap() {
	return this->is_map;
}

int Magic::getID() {
	return this->id;
}

void Magic::effectBattle(stagedata stage, Player* players, int user, int size_players, Enemy* enemy, int size_enemy) {
	DrawFormatString(100, 100, GetColor(0, 0, 0), "オーバーライドされていません。");
}

void Magic::effectMap() {
	DrawFormatString(100, 100, GetColor(0, 0, 0), "オーバーライドされていません。");
}

void Magic::draw_battle() {

}