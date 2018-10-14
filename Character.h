#pragma once

// キャラクターを定義するクラス
class Character {
private:
	char name[15]; // 名前。これで個体を管理する
	int x; //描画時のx座標
	int y; //描画時のy座標
	int hp; //現在体力
	int hp_max; //最大体力
	int attack; //攻撃力
	int diffence; //防御力
	int magic_power; //魔力
	int dex; //敏捷性
public:
	Character();
	Character(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex);
	void getName(int x, int y);
	int getX();
	void setX(int dx);
	int getY();
	void setY(int dy);
	int getHp();
	int getHpMax();
	void plusHp(int point);
	int getAttack();
	int getDiffence();
	int getMagicPower();
	int getDex();
};