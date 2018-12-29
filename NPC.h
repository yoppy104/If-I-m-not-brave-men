#pragma once
#include <vector>
#include <string>

using namespace std;

class NPC {
protected:
	char name[15];
	int x;
	int y;
	int image;
	int step;
	vector <char*> text;
	int text_box;
	
public:
	NPC();
	NPC(int pos_x, int pos_y, char name[], vector <char*> text);
	void getName(int x, int y);
	void draw(int x, int y, double disp_rate);
	int getX();
	int getY();
	virtual bool chat();
};