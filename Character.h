#pragma once
#include "DxLib.h"
#include "IDs.h"
#include <string>
#include <memory>

using Vector = struct {
	int x;	//x座標
	int y;	//y座標
};

using Status = struct {
	int hp;			//体力
	int hpMax;		//体力上限
	int attack;		//攻撃力
	int diffence;	//防御力
	int dex;		//敏捷性
	int magicPower;	//魔力
	int mp;			//MP
	int mpMax;		//MP上限
};

using Image = struct {
	int mapFront[2];			//mapでの正面画像
	int mapBack[2];				//mapでの背面画像
	int mapRight[4];			//mapでの右向画像
	int mapLeft[4];				//mapでの左向画像

	int battleWait[4];			//battleでの待機画像
	int battleMoveRight[4];		//battleでの右向き移動画像
	int battleMoveLeft[4];		//battleでの左向き移動画像
	int battleMoveUp[2];		//battleでの上向き移動画像
	int battleMoveDown[2];		//battleでの下向き移動画像
	int battleDead;				//battleでの行動不能時画像
	int battleAttackRight[4];	//battleでの右向き攻撃画像
	int battleAttackLeft[4];	//battleでの左向き攻撃画像
	int battleAttackUp[2];		//battleでの上向き攻撃画像
	int battleAttackDown[2];	//battleでの下向き攻撃画像
	int battleDamage[7];		//battleでのダメージ画像
	int battleUseSpecial[20];	//battleでの特殊攻撃、魔術など
};

// キャラクターを定義するクラス
class Character {
protected:
	ID id;				//id これで個体を管理する。
	std::string name;		//名前
	Vector pos;			//描画位置
	Status status;		//ステータス
	Image images;		//画像集
	bool hasMp;		//MPのステータスを持っているか
	bool is_moveable;	//行動可能かどうか

public:
	Character() = default;
	Character(ID id, int xpos, int ypos);

	void getName(int x, int y, int col) { DrawFormatString(x, y, col, name.c_str()); }
	int getX() const { return pos.x; }
	void setX(int dx) { pos.x = dx; }
	int getY() const { return pos.y; }
	void setY(int dy) { pos.y = dy; }
	int getHp() const { return status.hp; }
	int getHpMax() const { return status.hpMax; }
	void plusHp();
	void plusMp();
	void plusHp(int point);
	void plusMp(int point);
	virtual int getAttack() const { return status.attack; }
	virtual int getDiffence() const { return status.diffence; }
	int getMagicPower() const { return status.magicPower; }
	int getDex() const { return status.dex; }
	bool getHasMp() const { return hasMp; }
	void setHasMp(bool);
	void down();
	void alive();
	int getIsMoveable() const { return is_moveable; }
	int getId() { return id; };

	int getMp() { return status.mp; }
	int getMpMax() { return status.mpMax; }

	//player用
	virtual void move();
	virtual void battle();
	virtual bool is_attackable();
};