#pragma once
#include "Dxlib.h"
#include "M_Functions.h"
#include "Character.h"
#include "IDs.h"
#include <string>

/*
�T�v :	�G�̂ӂ�܂����`����N���X
		Player�Ɠ��l��Character���p������B
*/
class Enemy : public Character
{
	int charAniframe;	//�A�j���[�V�����p�̃t���[����
	bool active;		//�s���ł����Ԃ��ǂ���
	int Movetype;		//�ړ�����
	int Attacktype;		//�U������
	int gill;			//�|�����Ƃ��ɓ������
	int exp;			//�|�����Ƃ��ɓ�����o���l

public:
	Enemy() = default;
	Enemy(ID id, int x, int y);

	int DrawEnemy(int x, int y, int scene);
	bool GetActive();
	bool Activate();
	int Damage(int x);
	int Getattacktype();
	int Getmovetype();
	int GetGill();
	int GetEXP();

	void UpdateInMap(bool up, bool down, bool left, bool right);
	void DrawMap(int x, int y);

};

