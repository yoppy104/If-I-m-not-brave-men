#pragma once

#include <iostream>

using namespace std;

class Equipment{ // 装備の構造体
	int type; // 0:武器, 1:頭, 2:胴, 3:足, 4:アクセサリー
	int point; // 変動する値
	int price; // 購入時の値段
	int weight; // 重量。これによって装備できたりが変わる。
	int attackable;//同心円の範囲、-1の時は全範囲
	int attack_area;//攻撃範囲
	/*
	攻撃範囲は以下の様に定義する。
	10の位が
	1は1マス
	2は縦方向、1の位で長さを定義
	3は横方向、1の位で長さを定義
	4は同心円、1の位で半径を定義
	斜め方向の攻撃は定義しない
	*/
	
public:
	Equipment();
	Equipment(int type, int point, int price, int weight, int attackable, int attack_area);

	//パラメータ取り出し用の関数群
	int getAttackable();
};

