#pragma once
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

	int image_map_front[2] = { 0,0 };
	int image_map_back[2] = { 0,0 };
	int image_map_right[3] = { 0, 0, 0 };
	int image_map_left[3] = { 0, 0, 0 };
	
public:
	NPC();
	NPC(int pos_x, int pos_y, char name[], vector <string> text, int type);
	void getName(int x, int y);
	void draw(int x, int y);
	int getX();
	int getY();
	virtual bool chat();
	void change_direction(int xp, int yp);
};