#include "Enemy.h"



Enemy::Enemy(const char name[], int hp, int attack, int diffence, int magic_power, int dex, const char grafhic[],int TypeA,int TypeM) {
	strcpy(this->name, name);
	this->hp = hp;
	this->hp_max = hp;
	this->attack = attack;
	this->diffence = diffence;
	this->magic_power = magic_power;
	this->dex = dex;
	LoadDivGraph(grafhic, 1, 1, 1, 128, 128, gra);
	Attacktype = TypeA;
	Movetype = TypeM;
	gill = 30;
	exp = 150;

	charAniframe = 0;
	active = false;
}

int Enemy::DrawEnemy(double x, double y, int scene)
{
	float hpbar =128* hp / hp_max;
	switch (scene)
	{
	case 0:
		DrawGraph(x, y, gra[0], TRUE);
		DrawLineAA(x, y +3, x + hpbar, y +3, GetColor(0, 255, 0), 3);
		break;
	default:
		break;
	}
	return 0;
}

bool Enemy::GetActive()
{
	return active;
}

bool Enemy::Activate()
{
	active = !active;
	return true;
}

int Enemy::GetAGI()
{
	return dex;
}

int Enemy::Damage(int x)
{
	hp -= x;
	return 0;
}

int Enemy::GetAttack()
{
	return attack;
}

int Enemy::GetDex()
{
	return dex;
}

int Enemy::GetHp()
{
	return hp;
}

int Enemy::GetDiffence()
{
	return diffence;
}

int Enemy::Getattacktype(){
	return Attacktype;
}

int Enemy::Getmovetype(){
	return Movetype;
}

int Enemy::GetGill(){
	return gill;
}

int Enemy::GetEXP(){
	return exp;
}