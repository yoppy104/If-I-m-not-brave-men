#pragma once
#include "PartyControl.h"
#include <string>
#include "IDs.h"

typedef unsigned long long stagedata;

enum Type {
	NON,		//無属性
	FIRE,		//炎属性
	WATER,		//水属性
	THUNDER,	//雷属性
	GRASS,		//草属性
	WIND,		//風属性
	HOLLY,		//聖属性
	DARK,		//闇属性
	HEALER,		//回復魔術
	SUPPORT		//補助魔術
};

class Magic {
protected:
	string name;	//名前
	int cost;		//消費するmp
	bool is_map;	//マップ上で使えるかどうか
	ID id;			//魔術のid
	Type type;		//属性

	int point;		//攻撃力や回復力
	int usable_area;//使用する座標を選べる範囲の半径
	int effect_area;//指定座標からの効果適用範囲を表す数字

public:
	Magic();
	Magic(ID, string, int, bool);
	Magic(ID id);
	void getName(int, int);
	int getCost();
	bool getIsMap();
	ID getID();

	void effectBattle();	//戦闘での効果
	bool effectMap(std::shared_ptr<PartyControl> pc);	//マップ上での効果
	void draw_battle();	//バトルでのアニメーション
};