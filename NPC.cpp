#include "Npc.h"
#include "DxLib.h"
#include "M_Functions.h"

NPC::NPC(int pos_x, int pos_y, std:: string name, std::vector <std::string> text, int type) :
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
	text_box = LoadGraph("images\\System\\window.png");

	switch (type) {
	case 0:
		LoadDivGraph("images\\NPC\\Mob\\Man(Gold hair)\\【金髪男】Mobs32Dots_2Heads_WalkOnMap↑.png", 2, 2, 1, 64, 64, image.mapFront);
		LoadDivGraph("images\\NPC\\Mob\\Man(Gold hair)\\【金髪男】Mobs32Dots_2Heads_WalkOnMap↓.png", 2, 2, 1, 64, 64, image.mapBack);
		LoadDivGraph("images\\NPC\\Mob\\Man(Gold hair)\\【金髪男】Mobs32Dots_2Heads_WalkOnMap→.png", 3, 2, 2, 64, 64, image.mapRight);
		LoadDivGraph("images\\NPC\\Mob\\Man(Gold hair)\\【金髪男】Mobs32Dots_2Heads_WalkOnMap←.png", 3, 2, 2, 64, 64, image.mapLeft);
		break;
	case 1:
		LoadDivGraph("images\\NPC\\Mob\\Woman(Gold hair)\\【金髪女】Mobs32Dots_2Heads_WalkOnMap↑.png", 2, 2, 1, 64, 64, image.mapFront);
		LoadDivGraph("images\\NPC\\Mob\\Woman(Gold hair)\\【金髪女】Mobs32Dots_2Heads_WalkOnMap↓.png", 2, 2, 1, 64, 64, image.mapBack);
		LoadDivGraph("images\\NPC\\Mob\\Woman(Gold hair)\\【金髪女】Mobs32Dots_2Heads_WalkOnMap→.png", 3, 2, 2, 64, 64, image.mapRight);
		LoadDivGraph("images\\NPC\\Mob\\Woman(Gold hair)\\【金髪女】Mobs32Dots_2Heads_WalkOnMap←.png", 3, 2, 2, 64, 64, image.mapLeft);
		break;
	case 2:
		LoadDivGraph("images\\NPC\\Mob\\Man(Brond hair)\\【男】Mobs32Dots_2Heads_WalkOnMap↑.png", 2, 2, 1, 64, 64, image.mapFront);
		LoadDivGraph("images\\NPC\\Mob\\Man(Brond hair)\\【男】Mobs32Dots_2Heads_WalkOnMap↓.png", 2, 2, 1, 64, 64, image.mapBack);
		LoadDivGraph("images\\NPC\\Mob\\Man(Brond hair)\\【男】Mobs32Dots_2Heads_WalkOnMap→.png", 3, 2, 2, 64, 64, image.mapRight);
		LoadDivGraph("images\\NPC\\Mob\\Man(Brond hair)\\【男】Mobs32Dots_2Heads_WalkOnMap←.png", 3, 2, 2, 64, 64, image.mapLeft);
		break;

	}

}

//方向に応じて、アニメーションを変更する
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

//会話メソッド
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

//プレイヤーが話しかけた時に向きを変更する。
//引数はプレイヤーの座標
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