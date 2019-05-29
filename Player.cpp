#include <cmath>
#include "Player.h"
#include "Enemy.h"
#include "draw.h"
#include "DxLib.h"
#include "Mathematic.h"
#include <fstream>

typedef unsigned long long stagedata;

using namespace std;

Player::Player(ID id, int x, int y) :
Character(id, x, y),
LV(1),
exp{0, FIRST_EXP + 150, 0},
magicStone(0),
equipment{},
charAniframe(0),
active(false),
Block(false),
StaWindow(NULL),
Font(NULL),
numMagicMap(0)
{
	switch (id) {
	case ALLEN:		//アレンの場合
		status.mpMax = 10;
		status.mp = 10;
		status.hp = 20;
		status.hpMax = 20;
		status.attack = 10;
		status.diffence = 5;
		status.dex = 10;
		status.magicPower = 10;
		LoadDivGraph("images\\キャラチップ_アレン_正面.jpg", 2, 2, 1, 64, 64, images.mapFront);
		LoadDivGraph("images\\キャラチップ_アレン_背面1.jpg", 2, 2, 1, 64, 64, images.mapBack);
		LoadDivGraph("images\\キャラチップ_アレン_右.jpg", 4, 4, 1, 64, 64, images.mapRight);
		LoadDivGraph("images\\キャラチップ_アレン_左.jpg", 4, 4, 1, 64, 64, images.mapLeft);
		break;
	case IMITIA:	//イミティアの場合
		hasMp = false;
		status.mpMax = -1;
		status.mp = -1;
		status.hp = 20;
		status.hpMax = 20;
		status.attack = 10;
		status.diffence = 5;
		status.dex = 10;
		status.magicPower = 10;
		break;
	case CRAIG:		//クレイグの場合
		hasMp = false;
		status.mpMax = -1;
		status.mp = -1;
		status.hp = 20;
		status.hpMax = 20;
		status.attack = 10;
		status.diffence = 5;
		status.dex = 10;
		status.magicPower = 10;
		break;
	case RAIN:		//レインの場合
		hasMp = false;
		status.mpMax = -1;
		status.mp = -1;
		status.hp = 20;
		status.hpMax = 20;
		status.attack = 10;
		status.diffence = 5;
		status.dex = 10;
		status.magicPower = 10;
		break;
	}
}

Player::~Player() {
	magics.clear();
}

bool Player::GetActive()
{
	return active;
}

bool Player::Activate()
{
	active = !active;
	return true;
}

int Player::DrawChar(double x, double y, int scene)
{
	if (status.hp <= 0)
	{
		status.hp = 0;
		return 1;
	}
	switch (scene)
	{
	case 0:
		charAniframe %= 59;
		charAniframe++;
		DrawGraph(x, y, images.battleMoveRight[charAniframe / 30], TRUE);
		break;
	case 1:
		charAniframe %= 60;
		charAniframe++;
		DrawExtendGraph(x - 128, y, x + 129, y + 129, images.battleAttackRight[charAniframe / 15], TRUE);
		break;
	case 2:
		charAniframe %= 65;
		charAniframe++;
		DrawGraph(x - 64, y, images.battleDamage[charAniframe / 5], true);
		break;
	case 3:
		charAniframe %= 20;
		charAniframe++;
		DrawGraph(x, y, images.battleMoveRight[charAniframe / 5], true);
		break;
	default:
		break;
	}
	return 0;
}

int Player::GetAGI()
{
	return status.dex / 50 + 1;
}

int Player::Damage(int x)
{
	status.hp -= x;
	return 0;
}

int Player::getAttack() {
	return status.attack + equipment.weapon->getPoint();
}

int Player::getDiffence() {
	return status.diffence + equipment.head->getPoint() + equipment.arm->getPoint() + equipment.shield->getPoint() + equipment.chest->getPoint();
}

void Player::addMagic(ID id) {
	magics.push_back(std::make_shared<Magic>(Magic(id)));
	if (magics[magics.size() - 1]->getIsMap()) {
		numMagicMap++;
	}
}

void Player::plusMagicStone(int point) {
	magicStone += point;
}

int Player::sendEXp(int EXp) {
	exp.allEXP += EXp;
	exp.stuckEXP += EXp;
	bool can_LVUP = true;
	while (exp.NextEXP <= exp.stuckEXP)
	{
		exp.stuckEXP -= exp.NextEXP;
		exp.NextEXP = exp.NextEXP + 150 * pow(LV, 5.0 / 4.0);
		status.hpMax = status.hpMax + 2 * pow(LV, 0.25);
		status.attack = status.attack + pow(LV, 0.25);
		status.diffence = status.diffence + pow(LV, 0.25);
		status.dex = status.dex + pow(LV, 0.2);
		LV++;
	}
	return 0;
}

int Player::DrawSta(double x, double y)
{
	DrawFormatString(100, 100, GetColor(0, 0, 0), "test");
	if (status.hpMax<status.hp)
	{
		status.hp = status.hpMax;
	}
	double length = 68 + 300 * status.hp / status.hpMax;
	DrawExtendGraph(x, y, x + 400, y + 200, StaWindow, TRUE);
	DrawFormatStringToHandle(x + 15, y + 15, GetColor(0, 0, 0), Font, "%s", name);
	DrawFormatStringToHandle(x + 25, y + 65, GetColor(0, 0, 0), Font, "%d", status.hp);
	DrawFormatStringToHandle(x + 25, y + 115, GetColor(0, 0, 0), Font, "MP");
	DrawLineAA(x + 70, y + 65, x + 70, y + 95, GetColor(0, 0, 0), 5);
	DrawLineAA(x + 370, y + 65, x + 370, y + 95, GetColor(0, 0, 0), 5);
	DrawLineAA(x + 70, y + 113, x + 70, y + 143, GetColor(0, 0, 0), 5);
	DrawLineAA(x + 370, y + 113, x + 370, y + 143, GetColor(0, 0, 0), 5);
	DrawLineAA(x + 73, y + 80, x + length, y + 80, GetColor(0, 255, 0), 5);


	return 0;
}
int Player::ActBlock() {
	Block = true;
	if (Block)
	{
		status.diffence *= 2;
	}

	return 0;
}
int Player::ReleaseBlock() {
	if (Block)
	{
		status.diffence /= 2;
		Block = FALSE;
	}

	return 0;
}

int Player::SetAniframe(int x) {
	charAniframe = x;
	return 0;
}
int Player::GetLV() {
	return LV;
}

void Player::healHp(int delta) {
	status.hp += delta;
	if (status.hp > status.hpMax) {
		status.hp = status.hpMax;
	}
}

void Player::healHp() {
	status.hp = status.hpMax;
}

void Player::draw_map(int x, int y, int frame, int direction) {
	switch (direction) {
	case 0:
		DrawExtendGraph(x, y, x + 64, y + 64, images.mapFront[frame], TRUE);
		break;
	case 1:
		DrawExtendGraph(x, y, x + 64, y + 64, images.mapBack[frame], TRUE);
		break;
	case 2:
		DrawExtendGraph(x, y, x + 64, y + 64, images.mapRight[frame], TRUE);
		break;
	case 3:
		DrawExtendGraph(x, y, x + 64, y + 64, images.mapLeft[frame], TRUE);
		break;
	}
}

void Player::setEquipment(ID id, int type) {
	switch (type) {
	case 1:
		equipment.weapon = make_shared<Item>(Item(id));
		break;
	case 2:
		equipment.shield = make_shared<Item>(Item(id));
		break;
	case 3:
		equipment.chest = make_shared<Item>(Item(id));
		break;
	case 4:
		equipment.arm = make_shared<Item>(Item(id));
		break;
	case 5:
		equipment.head = make_shared<Item>(Item(id));
		break;
	}
}

void Player::setEquipment(const shared_ptr<Item> item, int type) {
	switch (type) {
	case 1:
		equipment.weapon = item;
		break;
	case 2:
		equipment.shield = item;
		break;
	case 3:
		equipment.chest = item;
		break;
	case 4:
		equipment.arm = item;
		break;
	case 5:
		equipment.head = item;
		break;
	}
}

