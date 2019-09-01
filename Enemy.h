#pragma once
#include "Dxlib.h"
#include "M_Functions.h"
#include "Character.h"
#include "IDs.h"
#include <string>

/*
概要 :	敵のふるまいを定義するクラス
		Playerと同様にCharacterを継承する。
*/
class Enemy : public Character
{
	int charAniframe;	//アニメーション用のフレーム数
	bool active;		//行動できる状態かどうか
	int Movetype;		//移動方式
	int Attacktype;		//攻撃方式
	int gill;			//倒したときに得られる金
	int exp;			//倒したときに得られる経験値

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

