#pragma once
#include "Dxlib.h"
#include "M_Functions.h"
#include <string.h>
class Enemy
{
	char name[15]; // 名前。これで個体を管理する
	int hp; //現在体力
	int hp_max; //最大体力
	int attack; //攻撃力
	int diffence; //防御力
	int magic_power; //魔力
	int dex; //敏捷性
	int gra[1];//グラフィックハンドル格納（とりあえず）
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

