#pragma once

#include "Weapon.h"
#include "Character.h"
#include <vector>
#include "Magic.h"
#include "Armor.h"
#include <memory>
#include <array>

#define FIRST_EXP 0

class Enemy;
class Magic;

typedef struct {
	shared_ptr<Weapon> weapon; //����
	shared_ptr<Armor> arm;		//�Ď�
	shared_ptr<Armor> head;	//��
	shared_ptr<Armor> chest;	//������
	shared_ptr<Armor> shield;	//��
} Equipment;

typedef struct {
	int allEXP;		//�S�o���l
	int NextEXP;	//���񃌃x���A�b�v�܂ł̌o���l
	int stuckEXP;	//�ݐόo���l
} EXP;

using namespace std;

class Player :public Character{ // �v���C���[�̍\���́A����������ŊǗ�
protected:
	vector <shared_ptr<Magic>> magics;
	EXP exp;

	int LV;
	int charAniframe;
	int StaWindow;
	int Font;
	bool active;
	bool Block;
	
	Equipment equipment;

	int magicStone; // ���΂̏�����


public:
	Player() = default;
	Player(ID id, int x, int y); // id�ɂ��R���X�g���N�^

	~Player();

	virtual int sendEXp(int EXp);

	int getMagicStone() { return magicStone; }
	void plusMagicStone(int);

	void addMagic(shared_ptr<Magic> new_magic);
	int getNumMagics() { return magics.size(); }
	vector <shared_ptr<Magic>> getMagics() { return magics; }
	shared_ptr<Magic> getMagic(int index) { return magics[index]; }
	int getAttack();
	int getDiffence();

	void healHp(int delta);
	void healHp();

	shared_ptr<Weapon> getWeapon();
	shared_ptr<Armor> getArmor(int type);

	void draw_map(int x, int y, int frame, int direction);

	void setEquipment(shared_ptr<Weapon> temp);
	void setEquipment(shared_ptr<Armor> temp, int type);

	int DrawSta(double x, double y);
	int ActBlock();
	int ReleaseBlock();
	int SetAniframe(int x);
	int GetLV();
	bool GetActive();
	bool Activate();
	int DrawChar(double x, double y, int scene);
	int GetAGI();
	int Damage(int x);
};