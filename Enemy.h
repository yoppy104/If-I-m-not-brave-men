#pragma once
#include "Dxlib.h"
#include "M_Functions.h"
#include <string.h>
class Enemy
{
	char name[15]; // ���O�B����Ō̂��Ǘ�����
	int hp; //���ݑ̗�
	int hp_max; //�ő�̗�
	int attack; //�U����
	int diffence; //�h���
	int magic_power; //����
	int dex; //�q����
	int gra[1];//�O���t�B�b�N�n���h���i�[�i�Ƃ肠�����j
	int charAniframe;
	bool active;
	int Movetype;
	int Attacktype;
	int gill;
	int exp;

public:
	Enemy(char name[], int hp, int attack, int diffence, int magic_power, int dex, char grafhic[],int TypeA,int TypeM);
	int DrawEnemy(double x, double y, int scene);
	bool GetActive();
	bool Activate();
	int GetAGI();
	int Damage(int x);
	int GetAttack();
	int GetDex();
	int GetHp();
	int GetDiffence();
	int Getattacktype();
	int Getmovetype();
	int GetGill();
	int GetEXP();
};

