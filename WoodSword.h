#pragma once

#include "Weapon.h"
#include "IDs.h"

class WoodSword :public Weapon {
private:

public:
	WoodSword();
	virtual void drawAttackableArea(); //攻撃可能エリアを描画
	virtual void selectAttack(); //攻撃範囲を選択
	virtual void drawAnimation(); //攻撃アニメーションを描画
	virtual bool effectBattle(); //戦闘時の効果、真偽値で使えるかを返す
	virtual bool effectMap();	 //マップ時の効果、真偽値で使えるかを返す。
};