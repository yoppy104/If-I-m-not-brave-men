#pragma once
#include "Item.h"

class Weapon : public Item{ // 装備の構造体
	int point; // 変動する値
	int weight; // 重量。これによって装備できたりが変わる。
	int sound;
	
public:
	Weapon();
	Weapon(char name[], int id, bool is_sell, int point, int price, int weight, int sound, int image);

	//パラメータ取り出し用の関数群
	int getPoint(); //効果点を取得
	int getSound(); //効果音を取得

	//戦闘時に呼び出すメソッド
	virtual void drawAttackableArea(); //攻撃可能エリアを描画
	virtual void selectAttack(); //攻撃範囲を選択
	virtual void drawAnimation(); //攻撃アニメーションを描画
	virtual bool effectBattle(); //戦闘時の効果
	virtual bool effectMap();
};

