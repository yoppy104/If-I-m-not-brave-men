#pragma once
#include "DxLib.h"
#include <vector>
#include <string>

/*
概要 :	NPCを定義するクラス
*/

class NPC {
protected:
	enum Direction {
		FRONT,
		BACK,
		RIGHT,
		LEFT
	};

	using Image = struct {
		int mapFront[2];
		int mapBack[2];
		int mapRight[3];
		int mapLeft[3];
	};

	std::string name;	//NPCの名前
	int x;				//x座標
	int y;				//y座標
	int step;			
	std::vector <std::string> text;	//会話の内容
	int text_box;		//会話を表示するテキストボックスの画像

	int frame;
	Direction direction;	//向いている方向

	Image image;			//画像

public:
	NPC() = default;
	NPC(int pos_x, int pos_y, std::string name, std::vector <std::string> text, int type);
	void getName(int x, int y) { DrawFormatString(x, y, GetColor(0, 0, 0), name.c_str()); }
	void draw(int x, int y);
	int getX() const { return x; }
	int getY() const { return y; }
	virtual bool chat();
	void change_direction(int xp, int yp);
};