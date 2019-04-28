#pragma once
#include "Weapon.h"
#include <string>

using namespace std; 

// キャラクターを定義するクラス
class Character {
protected:
	string name; // 名前。これで個体を管理する
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

	int image_map_front[2];	//mapでの正面画像
	int image_map_back[2];	//mapでの背面画像
	int image_map_right[4];	//mapでの右向画像
	int image_map_left[4];	//mapでの左向画像
public:
	Character();
	Character(string name, int x, int y, int hp, int attack, int diffence, int magic_power, int dex, int image, int image_dead);
	Character(int xpos, int ypos);
	void getName(int x, int y, int col);
	int getX();
	void setX(int dx);
	int getY();
	void setY(int dy);
	int getHp();
	int getHpMax();
	void plusHp(int point);
	virtual int getAttack();
	virtual int getDiffence();
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