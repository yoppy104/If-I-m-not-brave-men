#include "NPC.h"
#include "DxLib.h"
#include "M_Functions.h"

NPC::NPC(int pos_x, int pos_y, string name, vector <string> text, int type) :
	x(pos_x),
	y(pos_y),
	image{ 0, 0, 0, 0 },
	name(name),
	step(0),
	text(text),
	text_box(0),
	frame(0),
	direction(FRONT)
{
	text_box = LoadGraph("images\\window.png");

	switch (type) {
	case 0:
		LoadDivGraph("images\\y‹à”¯’jzMobs32Dots_2Heads_WalkOnMapª.png", 2, 2, 1, 64, 64, image.mapFront);
		LoadDivGraph("images\\y‹à”¯’jzMobs32Dots_2Heads_WalkOnMap«.png", 2, 2, 1, 64, 64, image.mapBack);
		LoadDivGraph("images\\y‹à”¯’jzMobs32Dots_2Heads_WalkOnMap¨.png", 3, 2, 2, 64, 64, image.mapRight);
		LoadDivGraph("images\\y‹à”¯’jzMobs32Dots_2Heads_WalkOnMap©.png", 3, 2, 2, 64, 64, image.mapLeft);
		break;
	case 1:
		LoadDivGraph("images\\y‹à”¯—zMobs32Dots_2Heads_WalkOnMapª.png", 2, 2, 1, 64, 64, image.mapFront);
		LoadDivGraph("images\\y‹à”¯—zMobs32Dots_2Heads_WalkOnMap«.png", 2, 2, 1, 64, 64, image.mapBack);
		LoadDivGraph("images\\y‹à”¯—zMobs32Dots_2Heads_WalkOnMap¨.png", 3, 2, 2, 64, 64, image.mapRight);
		LoadDivGraph("images\\y‹à”¯—zMobs32Dots_2Heads_WalkOnMap©.png", 3, 2, 2, 64, 64, image.mapLeft);
		break;
	case 2:
		LoadDivGraph("images\\y’jzMobs32Dots_2Heads_WalkOnMapª.png", 2, 2, 1, 64, 64, image.mapFront);
		LoadDivGraph("images\\y’jzMobs32Dots_2Heads_WalkOnMap«.png", 2, 2, 1, 64, 64, image.mapBack);
		LoadDivGraph("images\\y’jzMobs32Dots_2Heads_WalkOnMap¨.png", 3, 2, 2, 64, 64, image.mapRight);
		LoadDivGraph("images\\y’jzMobs32Dots_2Heads_WalkOnMap©.png", 3, 2, 2, 64, 64, image.mapLeft);
		break;

	}

}

void NPC::draw(int xx, int yy) {
	switch (direction) {
	case FRONT:
		DrawGraph(xx, yy, image.mapFront[(frame/15) % 2], TRUE);
		break;
	case BACK:
		DrawGraph(xx, yy, image.mapBack[(frame/15) % 2], TRUE);
		break;
	case RIGHT:
		DrawGraph(xx, yy, image.mapRight[(frame /15) % 3], TRUE);
		break;
	case LEFT:
		DrawGraph(xx, yy, image.mapLeft[(frame / 15) % 3], TRUE);
		break;
	}
	frame++;
}

bool NPC::chat() {
	if (step == text.size()) {
		step = 0;
		return true;
	}
	DrawExtendGraph(100, 800, 1860, 1000, text_box, TRUE);
	getName(120, 850);
	DrawFormatString(150, 900, GetColor(255, 255, 255), text[step].c_str());
	if (Button(KEY_INPUT_SPACE) == 1) {
		step++;
	}
	return false;
}

void NPC::change_direction(int xp, int yp) {
	if (yp > y){
		direction = FRONT;
	}
	else if (yp < y) {
		direction = BACK;
	}
	else if (xp > x) {
		direction = RIGHT;
	}
	else if (xp < x) {
		direction = LEFT;
	}
	frame = 0;
}