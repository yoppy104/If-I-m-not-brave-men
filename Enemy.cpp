#include "Enemy.h"
#include <time.h>



Enemy::Enemy(ID id, int x, int y) :
	Character(id, x, y),
	charAniframe(0),
	active(false),
	Movetype(0),
	Attacktype(0)
{
	switch (id) {
	case HORNRABIT:	//一角ウサギ
		status.attack = 50;
		status.dex = 10;
		status.diffence = 5;
		status.hpMax = 30;
		status.hp = status.hpMax;
		status.magicPower = 10;
		status.mpMax = 10;
		status.mp = status.mpMax;
		LoadDivGraph("images\\USAGI.png", 1, 1, 1, 128, 128, images.battleMoveRight);
		LoadDivGraph("images\\Usagi_Damage.png", 7, 7, 1, 128, 128, images.battleDamage);
		LoadDivGraph("images\\Usagi_Attack.png", 17, 7, 3, 256, 128, images.battleUseSpecial);
		LoadDivGraph("images\\Usagi_Walk_Map.png", 3, 3, 1, 64, 64, images.mapLeft);
		gill = 30;
		exp = 150;
		break;
	}
}

//アニメーションscene番号に応じて、変更
int Enemy::DrawEnemy(int x, int y, int scene)
{
	float hpbar =128* status.hp / status.hpMax;
	charAniframe++;
	switch (scene)
	{
	case 0:
		DrawGraph(x, y, images.battleMoveRight[0], TRUE);
		DrawLineAA(x, y +3, x + hpbar, y +3, GetColor(0, 255, 0), 3);
		break;
	case 1:
		break;
	case 2:
		DrawGraph(x, y, images.battleDamage[(charAniframe / 10) % 7], TRUE);
		break;
	case 3:
		DrawGraph(x, y, images.battleUseSpecial[(charAniframe / 10) % 17], TRUE);
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
	/*
	memo : バグの原因になったので修正
	*/
	charAniframe = 0;//アクティベートのたびにアニメの基準フレームも初期化する
	return true;
}

int Enemy::Damage(int x)
{
	status.hp -= x;
	return 0;
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

void Enemy::UpdateInMap(bool up, bool down, bool left, bool right) {
	if (charAniframe % 30 == 0) {
		int direction = GetRand(4);

		switch (direction)
		{
		case 0:		//上
			if (up) {
				pos.y--;
			}
			break;
		case 1:		//下
			if (down) {
				pos.y++;
			}
			break;
		case 2:		//左
			if (left) {
				pos.x--;
			}
			break;
		case 3:		//右
			if (right) {
				pos.x++;
			}
			break;
		default:
			break;
		}
	}

	charAniframe++;

}

void Enemy::DrawMap(int x, int y) {
	DrawGraph(x, y, images.mapLeft[(charAniframe / 10) % 3], TRUE);
}