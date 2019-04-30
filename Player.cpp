#include <cmath>
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "draw.h"
#include "DxLib.h"
#include "Mathematic.h"
#include <fstream>
#include "Items.h"

typedef unsigned long long stagedata;

Player::Player(ID id, int x, int y) :
Character(id, x, y),
LV(1),
exp{0, FIRST_EXP + 150, 0},
magicStone(0),
equipment{},
charAniframe(0),
active(false),
Block(false),
StaWindow(NULL)
{
	switch (id) {
	case ALLEN:		//アレンの場合
		this->status.mpMax = 10;
		this->status.mp = 10;
		this->status.hp = 20;
		this->status.hpMax = 20;
		this->status.attack = 10;
		this->status.diffence = 5;
		this->status.dex = 10;
		this->status.magicPower = 10;
		LoadDivGraph("キャラチップ_アレン_正面.jpg", 2, 2, 1, 64, 64, this->images.mapFront);
		LoadDivGraph("キャラチップ_アレン_背面1.jpg", 2, 2, 1, 64, 64, this->images.mapBack);
		LoadDivGraph("キャラチップ_アレン_右.jpg", 4, 4, 1, 64, 64, this->images.mapRight);
		LoadDivGraph("キャラチップ_アレン_左.jpg", 4, 4, 1, 64, 64, this->images.mapLeft);
		break;
	case IMITIA:	//イミティアの場合
		this->hasMp = false;
		this->status.mpMax = -1;
		this->status.mp = -1;
		this->status.hp = 20;
		this->status.hpMax = 20;
		this->status.attack = 10;
		this->status.diffence = 5;
		this->status.dex = 10;
		this->status.magicPower = 10;
		break;
	case CRAIG:		//クレイグの場合
		this->hasMp = false;
		this->status.mpMax = -1;
		this->status.mp = -1;
		this->status.hp = 20;
		this->status.hpMax = 20;
		this->status.attack = 10;
		this->status.diffence = 5;
		this->status.dex = 10;
		this->status.magicPower = 10;
		break;
	case RAIN:		//レインの場合
		this->hasMp = false;
		this->status.mpMax = -1;
		this->status.mp = -1;
		this->status.hp = 20;
		this->status.hpMax = 20;
		this->status.attack = 10;
		this->status.diffence = 5;
		this->status.dex = 10;
		this->status.magicPower = 10;
		break;
	}
}

Player::~Player() {
	this->magics.clear();
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
	return this->status.attack + this->equipment.weapon->getPoint();
}

int Player::getDiffence() {
	return this->status.diffence + this->equipment.head->getPoint() + this->equipment.arm->getPoint() + this->equipment.shield->getPoint() + this->equipment.chest->getPoint();
}

void Player::addMagic(shared_ptr<Magic> new_magic) {
	this->magics.push_back(new_magic);
}

void Player::plusMagicStone(int point) {
	this->magicStone += point;
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

shared_ptr<Weapon> Player::getWeapon() {
	return this->equipment.weapon;
}

shared_ptr<Armor> Player::getArmor(int type) {
	switch (type) {
	case 2:
		return this->equipment.shield;
		break;
	case 3:
		return this->equipment.chest;
		break;
	case 4:
		return this->equipment.arm;
		break;
	case 5:
		return this->equipment.head;
		break;
	}
}

void Player::healHp(int delta) {
	this->status.hp += delta;
	if (this->status.hp > this->status.hpMax) {
		this->status.hp = this->status.hpMax;
	}
}

void Player::healHp() {
	this->status.hp = this->status.hpMax;
}

void Player::draw_map(int x, int y, int frame, int direction) {
	switch (direction) {
	case 0:
		DrawExtendGraph(x, y, x + 64, y + 64, this->images.mapFront[frame], TRUE);
		break;
	case 1:
		DrawExtendGraph(x, y, x + 64, y + 64, this->images.mapBack[frame], TRUE);
		break;
	case 2:
		DrawExtendGraph(x, y, x + 64, y + 64, this->images.mapLeft[frame], TRUE);
		break;
	case 3:
		DrawExtendGraph(x, y, x + 64, y + 64, this->images.mapRight[frame], TRUE);
		break;
	}
}

void Player::setEquipment(shared_ptr<Weapon> temp) {
	this->equipment.weapon = temp;
}

void Player::setEquipment(shared_ptr<Armor> temp, int type) {
	switch (type) {
	case 2:
		this->equipment.shield = temp;
		break;
	case 3:
		this->equipment.chest = temp;
		break;
	case 4:
		this->equipment.arm = temp;
		break;
	case 5:
		this->equipment.head = temp;
		break;
	}
}

