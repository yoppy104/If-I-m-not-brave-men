#include <cmath>
#include "Player.h"
#include "Enemy.h"
#include "draw.h"
#include "DxLib.h"
#include "Mathematic.h"
#include <fstream>

Player::Player(ID id, int x, int y) :
Character(id, x, y),
LV(1),
exp{0, FIRST_EXP + 150, 0},
magicStone(0),
equipment{std::make_shared<Item>(Item(NOTEQUIPMENT)),
std::make_shared<Item>(Item(NOTEQUIPMENT)),
std::make_shared<Item>(Item(NOTEQUIPMENT)),
std::make_shared<Item>(Item(NOTEQUIPMENT)),
std::make_shared<Item>(Item(NOTEQUIPMENT))
},
charAniframe(0),
active(false),
Block(false),
StaWindow(NULL),
Font(NULL),
numMagicMap(1),
magics{
	std::make_shared<Magic>(Magic(FIREBALL)),
	std::make_shared<Magic>(Magic(HEAL))
}
{
	StaWindow = LoadGraph("images\\playerdata_gray.png");
	Font = CreateFontToHandle(NULL, 30, -1, DX_FONTTYPE_ANTIALIASING);
	switch (id) {
	case ALLEN:		//アレンの場合
		name = "アレン";
		status.mpMax = 10;
		status.mp = 10;
		status.hp = 20;
		status.hpMax = 20;
		status.attack = 1000;
		status.diffence = 5;
		status.dex = 10;
		status.magicPower = 10;
		LoadDivGraph("images\\キャラチップ_アレン_正面.jpg", 2, 2, 1, 64, 64, images.mapFront);
		LoadDivGraph("images\\キャラチップ_アレン_背面1.jpg", 2, 2, 1, 64, 64, images.mapBack);
		LoadDivGraph("images\\キャラチップ_アレン_右.jpg", 4, 4, 1, 64, 64, images.mapRight);
		LoadDivGraph("images\\キャラチップ_アレン_左.jpg", 4, 4, 1, 64, 64, images.mapLeft);
		LoadDivGraph("images\\Alen32Dots_Wait_Syagami_3.png", 4, 4, 1, 128, 128, images.battleWait);
		LoadDivGraph("images\\Alen32Dots_Walk.png", 4, 4, 1, 128, 128, images.battleMoveLeft);
		LoadDivGraph("images\\Alen32Dots_Damage2.png", 7, 7, 1, 128, 128, images.battleDamage);
		LoadDivGraph("images\\Alen32Dots_Attack_3.png", 4, 4, 1, 128, 128, images.battleAttackLeft);
		LoadDivGraph("images\\Alen32Dots_MagicCharge.png", 13, 13, 1, 128, 128, images.battleUseSpecial);
		break;
	case IMITIA:	//イミティアの場合
		name = "イミティア";
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
		name = "クレイグ";
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
		name = "レイン";
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

//アクティブかどうか
bool Player::GetActive()
{
	return active;
}

//画面上にキャラを表示するかどうか
bool Player::Activate()
{
	active = !active;
	return true;
}

//アニメーションメソッド
int Player::DrawChar(double x, double y, int scene)
{
	if (status.hp <= 0)
	{
		status.hp = 0;
		return 1;
	}

	charAniframe++;
	switch (scene)
	{
	/*
	修正した。
	インデックス内部で除算を使用するとOutOfRangeのエラーをはくときがある。
	そのため、必ず剰余を使用すること。
	*/
	case 0://バトル中の待機アニメーション
		DrawGraph(x, y, images.battleWait[(charAniframe / 30) % 4], TRUE);
		break;
	case 1://バトルでの攻撃アニメーション
		DrawExtendGraph(x - 128, y, x + 129, y + 129, images.battleAttackLeft[(charAniframe/10) % 4], TRUE);
		break;
	case 2://バトルでのダメージアニメーション
		DrawGraph(x - 64, y, images.battleDamage[(charAniframe/10) % 5], true);
		break;
	case 3://バトルでの移動アニメーション
		DrawGraph(x, y, images.battleMoveLeft[(charAniframe/30) % 4], true);
		break;
	case 4://バトルでの魔術使用時のアニメーション
		if (charAniframe > 64) {
			charAniframe = 54;
		}
		DrawExtendGraph(x, y, x + 128, y + 128, images.battleUseSpecial[(charAniframe / 5) % 13], true);
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

	//0未満にはならないようにする。
	if (status.hp < 0) {
		status.hp = 0;
	}
	return 0;
}

//能力値と武器の値を合算した数値を返す。
int Player::getAttack() {
	return status.attack + equipment.weapon->getPoint();
}

//能力値と防具の値を合算したス値を返す。
int Player::getDiffence() {
	return status.diffence + equipment.head->getPoint() + equipment.arm->getPoint() + equipment.shield->getPoint() + equipment.chest->getPoint();
}

//使用可能魔術を追加する。
void Player::addMagic(ID id) {
	magics.push_back(std::make_shared<Magic>(Magic(id)));
	if (magics[magics.size() - 1]->getIsMap()) {
		numMagicMap++;
	}
}

//所持魔晶石を増価させる。
void Player::plusMagicStone(int point) {
	magicStone += point;
}

//経験値を得る。
int Player::sendEXp(int EXp) {
	exp.allEXP += EXp;
	exp.stuckEXP += EXp;
	bool can_LVUP = true;

	//レベルアップ可能な間はレベルアップし続ける。
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

//ステータスを表示する。
int Player::DrawSta(double x, double y)
{
	if (status.hpMax<status.hp)
	{
		status.hp = status.hpMax;
	}
	int length = 68 + 300 * status.hp / status.hpMax;
	DrawExtendGraph(x, y, x + 400, y + 200, StaWindow, TRUE);
	getName(x + 15, y + 15, GetColor(0, 0, 0));
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

//マップでのアニメーション
void Player::draw_map(int x, int y, int frame, int direction) {
	switch (direction) {
	case 0:
		DrawGraph(x, y, images.mapFront[frame], TRUE);
		break;
	case 1:
		DrawGraph(x, y, images.mapBack[frame], TRUE);
		break;
	case 2:
		DrawGraph(x, y, images.mapRight[frame], TRUE);
		break;
	case 3:
		DrawGraph(x, y, images.mapLeft[frame], TRUE);
		break;
	}
}

//IDに基づいて装備を付ける。
item_ptr Player::setEquipment(ID id, int type) {
	item_ptr temp;
	switch (type) {
	case 1:
		temp = equipment.weapon;
		equipment.weapon = std::make_shared<Item>(Item(id));
		break;
	case 2:
		temp = equipment.shield;
		equipment.shield = std::make_shared<Item>(Item(id));
		break;
	case 3:
		temp = equipment.chest;
		equipment.chest = std::make_shared<Item>(Item(id));
		break;
	case 4:
		temp = equipment.arm;
		equipment.arm = std::make_shared<Item>(Item(id));
		break;
	case 5:
		temp = equipment.head;
		equipment.head = std::make_shared<Item>(Item(id));
		break;
	}
	return temp;
}

//ポインタに基づいて装備を付ける。
item_ptr Player::setEquipment(item_ptr item, int type) {
	item_ptr temp;
	switch (type) {
	case 1:
		temp = equipment.weapon;
		equipment.weapon = item;
		break;
	case 2:
		temp = equipment.shield;
		equipment.shield = item;
		break;
	case 3:
		temp = equipment.chest;
		equipment.chest = item;
		break;
	case 4:
		temp = equipment.arm;
		equipment.arm = item;
		break;
	case 5:
		temp = equipment.head;
		equipment.head = item;
		break;
	}
	return temp;
}

