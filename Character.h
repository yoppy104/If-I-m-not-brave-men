#pragma once
#include "Weapon.h"

// キャラクターを定義するクラス
class Character {
protected:
	char name[15]; // 名前。これで個体を管理する
	int x; //描画時のx座標
	int y; //描画時のy座標
	int hp; //現在体力
	int hp_max; //最大体力
	int attack; //攻撃力
	int diffence; //防御力
	int magic_power; //魔力
	int dex; //敏捷性
	bool has_mp; //MPのステータスを持っているか
	int image;
	int image_dead;
	bool is_moveable;
public:
	Character();
	Character(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, int image, int image_dead);
	void getName(int x, int y, int col);
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
	bool getHasMp();
	void setHasMp(bool);
	int getImage();
	int getImageDead();
	void down();
	void alive();
	int getIsMoveable();

	//Allen用
	virtual int getMp();

	//player用
	virtual void move();
	virtual void battle();
	virtual bool is_attackable();
	virtual Weapon* getWeapon();
};