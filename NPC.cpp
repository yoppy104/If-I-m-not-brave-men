#include "NPC.h"
#include <string.h>
#include "DxLib.h"
#include "M_Functions.h"

NPC::NPC() {

}

NPC::NPC(int pos_x, int pos_y, char name[], vector <char*> text) {
	this->x = pos_x;
	this->y = pos_y;
	this->image = LoadGraph("ƒvƒŒƒCƒ„[.png");
	strcpy(this->name, name);
	this->step = 0;
	this->text = text;
	this->text_box = LoadGraph("window.png");
}

void NPC::getName(int x, int y) {
	DrawFormatString(x, y, GetColor(0, 0, 0), this->name);
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
	DrawExtendGraph(100, 800, 1860, 1000, this->text_box, TRUE);
	this->getName(100, 950);
	DrawFormatString(150, 850, GetColor(255, 255, 255), this->text[this->step]);
	if (Button(KEY_INPUT_SPACE) == 1) {
		if (this->step == this->text.size()-1) {
			this->step = 0;
			return true;
		}
		this->step++;
	}
	else {
		return false;
	}
}