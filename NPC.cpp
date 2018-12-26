#include "NPC.h"
#include <string.h>
#include "DxLib.h"
#include "M_Functions.h"

NPC::NPC() {

}

NPC::NPC(int pos_x, int pos_y, char name[]) {
	this->x = pos_x;
	this->y = pos_y;
	this->image = LoadGraph("ƒvƒŒƒCƒ„[.png");
	strcpy(this->name, name);
}

void NPC::getName(int x, int y) {
	DrawFormatString(x, y, GetColor(255, 255, 255), this->name);
}

void NPC::draw(int xx, int yy, double disp_rate) {
	DrawExtendGraph(xx, yy, xx + 64 * disp_rate, yy + 64 * disp_rate, this->image, TRUE);
}

int NPC::getX() {
	return this->x;
}

int NPC::getY() {
	return this->y;
}

bool NPC::chat() {
	this->getName(100, 950);
	DrawFormatString(100, 1000, GetColor(255, 255, 255), "debug", TRUE);
	if (Button(KEY_INPUT_SPACE) == 1) {
		return true;
	}
	else {
		return false;
	}
}