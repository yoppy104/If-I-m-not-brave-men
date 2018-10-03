#pragma once

class Player;

typedef unsigned long long stagedata;

class Enemy // “G‚Ì\‘¢‘Ì
{
	char name[10]; // “G‚Ì–¼‘O
	int hp; // “G‚Ì‘Ì—Í
	int hp_max; //“G‚ÌÅ‘å‘Ì—Í
	int x; // “G‚ÌxÀ•W
	int y; // “G‚ÌyÀ•W
	int attack; // “G‚ÌUŒ‚—Í
	int diffence; // “G‚Ìç”õ—Í
	int image; // ‰æ‘œ

public:
	Enemy(char _name[], int _hp, int _x, int _y, int _attack, int _diffence, int _image);

	void move(Player* p, Enemy* e, int background_image, stagedata stage);

	int getX();
	int getY();
	int getAttack();
	int getDiffence();
	int getHp();
	void plusHp(int dp);
	int getImage();
};