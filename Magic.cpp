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

//ID���w�肷�邱�Ƃł��ꂼ��ɉ������C���X�^���X�𐶐�����R���X�g���N�^
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
		name = "�t�@�C�A�[�{�[��";
		cost = 5;
		is_map = false;
		point = 10;
		usable_area = 2;
		effect_area = 11;
		type = FIRE;
		LoadDivGraph("images\\Effects_Fire.png", 14, 4, 4, 128, 128, image.battle_animation);
		break;
	case HEAL:
		name = "�q�[��";
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

//�퓬�ł̌��ʏ���
void Magic::effectBattle() {
	//DrawFormatString(100, 100, GetColor(0, 0, 0), "�I�[�o�[���C�h����Ă��܂���B");
	switch (id) {
	case FIREBALL:
		break;
	case HEAL:
		break;
	}
}

//�}�b�v�ɂ�������ʏ���
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

//�퓬�ł̃A�j���[�V�����`��
void Magic::draw_battle(int x, int y, int anime_frame) {
	switch (id) {
	case FIREBALL:
		DrawGraph(x, y, image.battle_animation[(anime_frame / 10) % 9 + 5], TRUE);
		break;
	case HEAL:
		break;
	}
}