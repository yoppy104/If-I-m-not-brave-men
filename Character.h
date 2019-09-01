#pragma once
#include "DxLib.h"
#include "IDs.h"
#include <string>
#include <memory>

using Vector = struct {
	int x;	//x���W
	int y;	//y���W
};

using Status = struct {
	int hp;			//�̗�
	int hpMax;		//�̗͏��
	int attack;		//�U����
	int diffence;	//�h���
	int dex;		//�q����
	int magicPower;	//����
	int mp;			//MP
	int mpMax;		//MP���
};

using Image = struct {
	int mapFront[2];			//map�ł̐��ʉ摜
	int mapBack[2];				//map�ł̔w�ʉ摜
	int mapRight[4];			//map�ł̉E���摜
	int mapLeft[4];				//map�ł̍����摜

	int battleWait[4];			//battle�ł̑ҋ@�摜
	int battleMoveRight[4];		//battle�ł̉E�����ړ��摜
	int battleMoveLeft[4];		//battle�ł̍������ړ��摜
	int battleMoveUp[2];		//battle�ł̏�����ړ��摜
	int battleMoveDown[2];		//battle�ł̉������ړ��摜
	int battleDead;				//battle�ł̍s���s�\���摜
	int battleAttackRight[4];	//battle�ł̉E�����U���摜
	int battleAttackLeft[4];	//battle�ł̍������U���摜
	int battleAttackUp[2];		//battle�ł̏�����U���摜
	int battleAttackDown[2];	//battle�ł̉������U���摜
	int battleDamage[7];		//battle�ł̃_���[�W�摜
	int battleUseSpecial[20];	//battle�ł̓���U���A���p�Ȃ�
};

// �L�����N�^�[���`����N���X
class Character {
protected:
	ID id;				//id ����Ō̂��Ǘ�����B
	std::string name;		//���O
	Vector pos;			//�`��ʒu
	Status status;		//�X�e�[�^�X
	Image images;		//�摜�W
	bool hasMp;		//MP�̃X�e�[�^�X�������Ă��邩
	bool is_moveable;	//�s���\���ǂ���

public:
	Character() = default;
	Character(ID id, int xpos, int ypos);

	void getName(int x, int y, int col) { DrawFormatString(x, y, col, name.c_str()); }
	int getX() const { return pos.x; }
	void setX(int dx) { pos.x = dx; }
	int getY() const { return pos.y; }
	void setY(int dy) { pos.y = dy; }
	int getHp() const { return status.hp; }
	int getHpMax() const { return status.hpMax; }
	void plusHp();
	void plusMp();
	void plusHp(int point);
	void plusMp(int point);
	virtual int getAttack() const { return status.attack; }
	virtual int getDiffence() const { return status.diffence; }
	int getMagicPower() const { return status.magicPower; }
	int getDex() const { return status.dex; }
	bool getHasMp() const { return hasMp; }
	void setHasMp(bool);
	void down();
	void alive();
	int getIsMoveable() const { return is_moveable; }
	int getId() { return id; };

	int getMp() { return status.mp; }
	int getMpMax() { return status.mpMax; }

	//player�p
	virtual void move();
	virtual void battle();
	virtual bool is_attackable();
};