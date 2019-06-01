#pragma once
#include "DxLib.h"
#include <vector>
#include <string>



class NPC {
protected:
	enum Direction {
		FRONT,
		BACK,
		RIGHT,
		LEFT
	};

	typedef struct {
		int mapFront[2];
		int mapBack[2];
		int mapRight[3];
		int mapLeft[3];
	} Image;

	std::string name;
	int x;
	int y;
	int step;
	std::vector <std::string> text;
	int text_box;

	int frame;
	Direction direction;

	Image image;

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