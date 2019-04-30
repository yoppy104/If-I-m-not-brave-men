#pragma once
#include "PartyControl.h"
#include <string>

typedef unsigned long long stagedata;

class Player;
class Enemy;
class PartyControl;

enum Type {
	FIRE,		//������
	WATER,		//������
	THUNDER,	//������
	GRASS,		//������
	WIND,		//������
	HOLLY,		//������
	DARK,		//�ő���
	HEALER,		//�񕜖��p
	SUPPORT		//�⏕���p
};

class Magic {
protected:
	string name;	//���O
	int cost;		//�����mp
	bool is_map;	//�}�b�v��Ŏg���邩�ǂ���
	int id;			//���p��id
	int type;		//����

	int point;		//�U���͂�񕜗�
	int usable_area;//�g�p������W��I�ׂ�͈͂̔��a
	int effect_area;//�w����W����̌��ʓK�p�͈͂�\������

public:
	Magic();
	Magic(int, string, int, bool);
	Magic(int id);
	void getName(int, int);
	int getCost();
	bool getIsMap();
	int getID();

	void effectBattle(stagedata stage, Player* players, int user, int size_players, Enemy* enemy, int size_enemy);	//�퓬�ł̌���
	bool effectMap(shared_ptr<PartyControl> pc);	//�}�b�v��ł̌���
	void draw_battle();	//�o�g���ł̃A�j���[�V����
};