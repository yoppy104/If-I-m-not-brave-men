#pragma once
#include "DxLib.h"
#include <vector>
#include <string>

/*
�T�v :	NPC���`����N���X
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

	std::string name;	//NPC�̖��O
	int x;				//x���W
	int y;				//y���W
	int step;			
	std::vector <std::string> text;	//��b�̓��e
	int text_box;		//��b��\������e�L�X�g�{�b�N�X�̉摜

	int frame;
	Direction direction;	//�����Ă������

	Image image;			//�摜

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