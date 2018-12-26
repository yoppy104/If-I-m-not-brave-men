#pragma once

class NPC {
protected:
	char name[15];
	int x;
	int y;
	int image;
	
public:
	NPC();
	NPC(int pos_x, int pos_y, char name[]);
	void getName(int x, int y);
	void draw(int x, int y, double disp_rate);
	int getX();
	int getY();
	virtual bool chat();
};