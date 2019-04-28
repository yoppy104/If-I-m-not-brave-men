#include "NPC.h"
#include "DxLib.h"
#include "M_Functions.h"

NPC::NPC() {

}

NPC::NPC(int pos_x, int pos_y, char name[], vector <string> text, int type) {
	this->x = pos_x;
	this->y = pos_y;
	this->image = LoadGraph("ƒvƒŒƒCƒ„[.png");
	this->name = name;
	this->step = 0;
	this->text = text;
	this->text_box = LoadGraph("window.png");

	this->frame = 0;
	this->direction = 0;

	switch (type) {
	case 0:
		LoadDivGraph("y‹à”¯’jzMobs32Dots_2Heads_WalkOnMapª.png", 2, 2, 1, 64, 64, this->image_map_front);
		LoadDivGraph("y‹à”¯’jzMobs32Dots_2Heads_WalkOnMap«.png", 2, 2, 1, 64, 64, this->image_map_back);
		LoadDivGraph("y‹à”¯’jzMobs32Dots_2Heads_WalkOnMap¨.png", 3, 2, 2, 64, 64, this->image_map_right);
		LoadDivGraph("y‹à”¯’jzMobs32Dots_2Heads_WalkOnMap©.png", 3, 2, 2, 64, 64, this->image_map_left);
		break;
	case 1:
		LoadDivGraph("y‹à”¯—zMobs32Dots_2Heads_WalkOnMapª.png", 2, 2, 1, 64, 64, this->image_map_front);
		LoadDivGraph("y‹à”¯—zMobs32Dots_2Heads_WalkOnMap«.png", 2, 2, 1, 64, 64, this->image_map_back);
		LoadDivGraph("y‹à”¯—zMobs32Dots_2Heads_WalkOnMap¨.png", 3, 2, 2, 64, 64, this->image_map_right);
		LoadDivGraph("y‹à”¯—zMobs32Dots_2Heads_WalkOnMap©.png", 3, 2, 2, 64, 64, this->image_map_left);
		break;
	case 2:
		LoadDivGraph("y’jzMobs32Dots_2Heads_WalkOnMapª.png", 2, 2, 1, 64, 64, this->image_map_front);
		LoadDivGraph("y’jzMobs32Dots_2Heads_WalkOnMap«.png", 2, 2, 1, 64, 64, this->image_map_back);
		LoadDivGraph("y’jzMobs32Dots_2Heads_WalkOnMap¨.png", 3, 2, 2, 64, 64, this->image_map_right);
		LoadDivGraph("y’jzMobs32Dots_2Heads_WalkOnMap©.png", 3, 2, 2, 64, 64, this->image_map_left);
		break;

	}

}

void NPC::getName(int x, int y) {
	DrawFormatString(x, y, GetColor(0, 0, 0), this->name.c_str());
}

void NPC::draw(int xx, int yy) {
	switch (this->direction) {
	case 0:
		DrawGraph(xx, yy, this->image_map_front[(this->frame/15) % 2], TRUE);
		break;
	case 1:
		DrawGraph(xx, yy, this->image_map_back[(this->frame/15) % 2], TRUE);
		break;
	case 2:
		DrawGraph(xx, yy, this->image_map_right[(this->frame /15) % 3], TRUE);
		break;
	case 3:
		DrawGraph(xx, yy, this->image_map_left[(this->frame / 15) % 3], TRUE);
		break;
	}
	this->frame++;
}

int NPC::getX() {
	return this->x;
}

int NPC::getY() {
	return this->y;
}

bool NPC::chat() {
	if (this->step == this->text.size()) {
		this->step = 0;
		return true;
	}
	DrawExtendGraph(100, 800, 1860, 1000, this->text_box, TRUE);
	this->getName(120, 850);
	DrawFormatString(150, 900, GetColor(255, 255, 255), this->text[this->step].c_str());
	if (Button(KEY_INPUT_SPACE) == 1) {
		this->step++;
	}
	return false;
}

void NPC::change_direction(int xp, int yp) {
	if (yp > this->y){
		this->direction = 0;
	}
	else if (yp < this->y) {
		this->direction = 1;
	}
	else if (xp > this->x) {
		this->direction = 2;
	}
	else if (xp < this->x) {
		this->direction = 3;
	}
	this->frame = 0;
}