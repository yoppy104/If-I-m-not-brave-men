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

Player::Player() {

}

Player::Player(string name, int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon* weapon, Armor* head, Armor* arm, Armor* chest, Armor* shield, int image, int image_dead):Character(name, x, y, hp, attack, diffence, magic_power, dex, image, image_dead){
	this->weapon = weapon; //装備
	this->head = head;
	this->arm = arm;
	this->shield = shield;
	this->chest = chest;
	
	this->NextEXP = FIRST_EXP + 150;
	this->LV = 1;
	LoadDivGraph("Alen.png", 2, 2, 1, 128, 128, gra);
	this->StaWindow = LoadGraph("playerdata_gray.png");
	LoadDivGraph("Alen32Dots_Attack_3.png", 4, 4, 1, 128, 64, AllenAttack);
	LoadDivGraph("Alen32Dots_MagicCharge.png", 13, 13, 1, 128, 64, Allendamage);
	LoadDivGraph("Alen32Dots_Walk.png", 4, 4, 1, 128, 128, AllenWalk);
	this->charAniframe = 0;
	this->Font = CreateFontToHandle(NULL, 30, -1, DX_FONTTYPE_ANTIALIASING);
	this->active = false;
	this->Block = false;
	this->allEXP = 0;
	this->stuckEXP = 0;
}

Player::Player(string name, int x, int y) :Character() {
	this->x = x;
	this->y = y;
}

Player::Player(int id, int x, int y) :
Character(x, y),//エラー箇所だと思う
LV(1),
id(id),
allEXP(0),
NextEXP(FIRST_EXP + 150),
stuckEXP(0),
has_mp(NULL),
mp_max(NULL),
mp(NULL),
magicstone(0),
weapon(NULL),
head(NULL),
arm(NULL),
shield(NULL),
chest(NULL),
charAniframe(0),
Font(NULL),
active(false),
Block(false),
StaWindow(NULL)
{
	switch (id) {
	case ALLEN:		//アレンの場合
		this->mp_max = 10;
		this->mp = 10;
		this->hp = 20;
		this->attack = 10;
		this->diffence = 5;
		this->dex = 10;
		this->magic_power = 10;
		LoadDivGraph("キャラチップ_アレン_正面.jpg", 2, 2, 1, 64, 64, this->image_map_front);
		LoadDivGraph("キャラチップ_アレン_背面1.jpg", 2, 2, 1, 64, 64, this->image_map_back);
		LoadDivGraph("キャラチップ_アレン_右.jpg", 4, 4, 1, 64, 64, this->image_map_right);
		LoadDivGraph("キャラチップ_アレン_左.jpg", 4, 4, 1, 64, 64, this->image_map_left);
		break;
	case IMITIA:	//イミティアの場合
		this->has_mp = false;
		this->mp_max = -1;
		this->mp = -1;
		this->hp = 20;
		this->attack = 10;
		this->diffence = 5;
		this->dex = 10;
		this->magic_power = 10;
		break;
	case CRAIG:		//クレイグの場合
		this->has_mp = false;
		this->mp_max = -1;
		this->mp = -1;
		this->hp = 20;
		this->attack = 10;
		this->diffence = 5;
		this->dex = 10;
		this->magic_power = 10;
		break;
	case RAIN:		//レインの場合
		this->has_mp = false;
		this->mp_max = -1;
		this->mp = -1;
		this->hp = 20;
		this->attack = 10;
		this->diffence = 5;
		this->dex = 10;
		this->magic_power = 10;
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
	if (hp <= 0)
	{
		hp = 0;
		return 1;
	}
	switch (scene)
	{
	case 0:
		charAniframe %= 59;
		charAniframe++;
		DrawGraph(x, y, gra[charAniframe / 30], TRUE);
		break;
	case 1:
		charAniframe %= 60;
		charAniframe++;
		DrawExtendGraph(x - 128, y, x + 129, y + 129, AllenAttack[charAniframe / 15], TRUE);
		break;
	case 2:
		charAniframe %= 65;
		charAniframe++;
		DrawGraph(x - 64, y, Allendamage[charAniframe / 5], true);
		break;
	case 3:
		charAniframe %= 20;
		charAniframe++;
		DrawGraph(x, y, AllenWalk[charAniframe / 5], true);
		break;
	default:
		break;
	}
	return 0;
}

int Player::GetAGI()
{
	return dex / 50 + 1;
}

int Player::Damage(int x)
{
	hp -= x;
	return 0;
}

int Player::getAttack() {
	return this->attack + this->weapon->getPoint();
}

int Player::getDiffence() {
	return this->diffence + this->head->getPoint() + this->arm->getPoint() + this->shield->getPoint() + this->chest->getPoint();
}

void Player::addMagic(Magic* new_magic) {
	this->magics.push_back(new_magic);
}

int Player::getNumMagics() {
	return this->magics.size();
}

vector <Magic*> Player::getMagics() {
	return this->magics;
}

Magic* Player::getMagic(int index) {
	return this->magics[index];
}

int Player::getMagicStone() {
	return 0;
}
void Player::plusMagicStone(int point) {
	this->magicstone += point;
}

int Player::sendEXp(int EXp) {
	allEXP += EXp;
	stuckEXP += EXp;
	bool can_LVUP = true;
	while (NextEXP <= stuckEXP)
	{
		stuckEXP -= NextEXP;
		NextEXP = NextEXP + 150 * pow(LV, 5.0 / 4.0);
		hp_max = hp_max + 2 * pow(LV, 0.25);
		attack = attack + pow(LV, 0.25);
		diffence = diffence + pow(LV, 0.25);
		dex = dex + pow(LV, 0.2);
		LV++;
	}
	return 0;
}

int Player::DrawSta(double x, double y)
{
	DrawFormatString(100, 100, GetColor(0, 0, 0), "test");
	if (hp_max<hp)
	{
		hp = hp_max;
	}
	double length = 68 + 300 * hp / hp_max;
	DrawExtendGraph(x, y, x + 400, y + 200, StaWindow, TRUE);
	DrawFormatStringToHandle(x + 15, y + 15, GetColor(0, 0, 0), Font, "%s", name);
	DrawFormatStringToHandle(x + 25, y + 65, GetColor(0, 0, 0), Font, "%d", hp);
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
		diffence *= 2;
	}

	return 0;
}
int Player::ReleaseBlock() {
	if (Block)
	{
		diffence /= 2;
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

Weapon* Player::getWeapon() {
	return this->weapon;
}

Armor* Player::getArmor(int type) {
	switch (type) {
	case 2:
		return this->shield;
		break;
	case 3:
		return this->chest;
		break;
	case 4:
		return this->arm;
		break;
	case 5:
		return this->head;
		break;
	}
}

void Player::plusMp(int point) {

}

void Player::plusMp() {

}

int Player::getMpMax() {
	return 0;
}

void Player::healHp(int delta) {
	this->hp += delta;
	if (this->hp > this->hp_max) {
		this->hp = this->hp_max;
	}
}

void Player::healHp() {
	this->hp = this->hp_max;
}

int Player::getMp() {
	return 3;
}

int Player::getId() {
	return this->id;
}

void Player::draw_map(int x, int y, int frame, int direction) {
	switch (direction) {
	case 0:
		DrawExtendGraph(x, y, x + 64, y + 64, this->image_map_front[frame], TRUE);
		break;
	case 1:
		DrawExtendGraph(x, y, x + 64, y + 64, this->image_map_back[frame], TRUE);
		break;
	case 2:
		DrawExtendGraph(x, y, x + 64, y + 64, this->image_map_left[frame], TRUE);
		break;
	case 3:
		DrawExtendGraph(x, y, x + 64, y + 64, this->image_map_right[frame], TRUE);
		break;
	}
}

void Player::setEquipment(Weapon* temp) {
	this->weapon = temp;
}

void Player::setEquipment(Armor* temp, int type) {
	switch (type) {
	case 2:
		this->shield = temp;
		break;
	case 3:
		this->chest = temp;
		break;
	case 4:
		this->arm = temp;
		break;
	case 5:
		this->head = temp;
		break;
	}
}