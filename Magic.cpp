#include "Magic.h"
#include "DxLib.h"
#include "IDs.h"
#include "Player.h"


Magic::Magic() :
	name("NULL"),
	cost(NULL),
	is_map(NULL),
	id(UNDIFINED),
	point(NULL),
	usable_area(NULL),
	effect_area(NULL),
	type(NON)
{

}

Magic::Magic(ID id, std::string name, int cost, bool map) :
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

//IDを指定することでそれぞれに応じたインスタンスを生成するコンストラクタ
Magic::Magic(ID id) :
	name("NULL"),
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
		LoadDivGraph("images\\Effects_Fire.png", 14, 4, 4, 128, 128, image.battle_animation);
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

//戦闘での効果処理
void Magic::effectBattle() {
	//DrawFormatString(100, 100, GetColor(0, 0, 0), "オーバーライドされていません。");
	switch (id) {
	case FIREBALL:
		break;
	case HEAL:
		break;
	}
}

//マップにおける効果処理
bool Magic::effectMap(std::shared_ptr<Player> player) {
	if (is_map) {
		switch (id)
		{
		case HEAL:
			player->plusHp(point);
			if (player->getHasMp()) {
				player->plusMp(cost);
			}
			break;
		default:
			break;
		}
		return true;
	}
	return false;

}

//戦闘でのアニメーション描画
void Magic::draw_battle(int x, int y, int anime_frame) {
	switch (id) {
	case FIREBALL:
		DrawGraph(x, y, image.battle_animation[(anime_frame / 10) % 9 + 5], TRUE);
		break;
	case HEAL:
		break;
	}
}