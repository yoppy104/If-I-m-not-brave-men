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
	case ALLEN:		//�A�����̏ꍇ
		name = "�A����";
		status.mpMax = 10;
		status.mp = 10;
		status.hp = 20;
		status.hpMax = 20;
		status.attack = 1000;
		status.diffence = 5;
		status.dex = 10;
		status.magicPower = 10;
		LoadDivGraph("images\\�L�����`�b�v_�A����_����.jpg", 2, 2, 1, 64, 64, images.mapFront);
		LoadDivGraph("images\\�L�����`�b�v_�A����_�w��1.jpg", 2, 2, 1, 64, 64, images.mapBack);
		LoadDivGraph("images\\�L�����`�b�v_�A����_�E.jpg", 4, 4, 1, 64, 64, images.mapRight);
		LoadDivGraph("images\\�L�����`�b�v_�A����_��.jpg", 4, 4, 1, 64, 64, images.mapLeft);
		LoadDivGraph("images\\Alen32Dots_Wait_Syagami_3.png", 4, 4, 1, 128, 128, images.battleWait);
		LoadDivGraph("images\\Alen32Dots_Walk.png", 4, 4, 1, 128, 128, images.battleMoveLeft);
		LoadDivGraph("images\\Alen32Dots_Damage2.png", 7, 7, 1, 128, 128, images.battleDamage);
		LoadDivGraph("images\\Alen32Dots_Attack_3.png", 4, 4, 1, 128, 128, images.battleAttackLeft);
		LoadDivGraph("images\\Alen32Dots_MagicCharge.png", 13, 13, 1, 128, 128, images.battleUseSpecial);
		break;
	case IMITIA:	//�C�~�e�B�A�̏ꍇ
		name = "�C�~�e�B�A";
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
	case CRAIG:		//�N���C�O�̏ꍇ
		name = "�N���C�O";
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
	case RAIN:		//���C���̏ꍇ
		name = "���C��";
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

//�A�N�e�B�u���ǂ���
bool Player::GetActive()
{
	return active;
}

//��ʏ�ɃL������\�����邩�ǂ���
bool Player::Activate()
{
	active = !active;
	return true;
}

//�A�j���[�V�������\�b�h
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
	�C�������B
	�C���f�b�N�X�����ŏ��Z���g�p�����OutOfRange�̃G���[���͂��Ƃ�������B
	���̂��߁A�K����]���g�p���邱�ƁB
	*/
	case 0://�o�g�����̑ҋ@�A�j���[�V����
		DrawGraph(x, y, images.battleWait[(charAniframe / 30) % 4], TRUE);
		break;
	case 1://�o�g���ł̍U���A�j���[�V����
		DrawExtendGraph(x - 128, y, x + 129, y + 129, images.battleAttackLeft[(charAniframe/10) % 4], TRUE);
		break;
	case 2://�o�g���ł̃_���[�W�A�j���[�V����
		DrawGraph(x - 64, y, images.battleDamage[(charAniframe/10) % 5], true);
		break;
	case 3://�o�g���ł̈ړ��A�j���[�V����
		DrawGraph(x, y, images.battleMoveLeft[(charAniframe/30) % 4], true);
		break;
	case 4://�o�g���ł̖��p�g�p���̃A�j���[�V����
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

	//0�����ɂ͂Ȃ�Ȃ��悤�ɂ���B
	if (status.hp < 0) {
		status.hp = 0;
	}
	return 0;
}

//�\�͒l�ƕ���̒l�����Z�������l��Ԃ��B
int Player::getAttack() {
	return status.attack + equipment.weapon->getPoint();
}

//�\�͒l�Ɩh��̒l�����Z�����X�l��Ԃ��B
int Player::getDiffence() {
	return status.diffence + equipment.head->getPoint() + equipment.arm->getPoint() + equipment.shield->getPoint() + equipment.chest->getPoint();
}

//�g�p�\���p��ǉ�����B
void Player::addMagic(ID id) {
	magics.push_back(std::make_shared<Magic>(Magic(id)));
	if (magics[magics.size() - 1]->getIsMap()) {
		numMagicMap++;
	}
}

//���������΂𑝉�������B
void Player::plusMagicStone(int point) {
	magicStone += point;
}

//�o���l�𓾂�B
int Player::sendEXp(int EXp) {
	exp.allEXP += EXp;
	exp.stuckEXP += EXp;
	bool can_LVUP = true;

	//���x���A�b�v�\�ȊԂ̓��x���A�b�v��������B
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

//�X�e�[�^�X��\������B
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

//�}�b�v�ł̃A�j���[�V����
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

//ID�Ɋ�Â��đ�����t����B
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

//�|�C���^�Ɋ�Â��đ�����t����B
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

