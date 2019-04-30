#pragma once
#include "DxLib.h"
#include <vector>
#include <string>

using namespace std;

class NPC {
protected:
	string name;
	int x;
	int y;
	int image;
	int step;
	vector <string> text;
	int text_box;

	int frame;
	int direction;

	int image_map_front[2];
	int image_map_back[2];
	int image_map_right[3];
	int image_map_left[3];
	
public:
	NPC();
	NPC(int pos_x, int pos_y, char name[], vector <string> text, int type);
	void getName(int x, int y) { DrawFormatString(x, y, GetColor(0, 0, 0), this->name.c_str()); }
	void draw(int x, int y);
	int getX() const { return x; }
	int getY() const { return y; }
	virtual bool chat();
	void change_direction(int xp, int yp);
};