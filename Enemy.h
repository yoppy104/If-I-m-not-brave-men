#pragma once

class Player;

typedef unsigned long long stagedata;

class Enemy // �G�̍\����
{
	char name[10]; // �G�̖��O
	int hp; // �G�̗̑�
	int x; // �G��x���W
	int y; // �G��y���W
	int attack; // �G�̍U����
	int diffence; // �G�̎����
	int image; // �摜

public:
	Enemy(char _name[], int _hp, int _x, int _y, int _attack, int _diffence, int _image);

	void move(Player* p, Enemy* e, int background_image, stagedata stage);

	int getX();
	int getY();
	int getImage();
};