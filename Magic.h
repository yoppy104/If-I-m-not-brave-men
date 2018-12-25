#pragma once

typedef unsigned long long stagedata;

class Player;
class Enemy;

class Magic {
private:
	char name[16];
	int cost;
	bool is_map;
	int id;

	virtual void effectpoint();

public:
	Magic();
	Magic(int, char*, int, bool);
	void getName(int, int);
	int getCost();
	bool getIsMap();
	int getID();

	virtual void effectBattle(stagedata stage, Player* players, int user, int size_players, Enemy* enemy, int size_enemy);
	virtual void effectMap();
	virtual void draw_battle();
};