#pragma once
#include <string>
#include <memory>
#include "IDs.h"

class Player;

/*
�T�v :	���p�p�̃N���X
*/

//����
enum Type {
	NON,		//������
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
	//�摜�\���́B�������邽�߃����o
	using Image = struct {
		int battle_animation[16];
	};

	std::string name;	//���O
	int cost;		//�����mp
	bool is_map;	//�}�b�v��Ŏg���邩�ǂ���
	ID id;			//���p��id
	Type type;		//����

	Image image;

	int point;		//�U���͂�񕜗�
	int usable_area;//�g�p������W��I�ׂ�͈͂̔��a
	int effect_area;//�w����W����̌��ʓK�p�͈͂�\������

public:
	Magic();
	Magic(ID, std::string, int, bool);
	Magic(ID id);
	void getName(int, int);
	int getCost();
	bool getIsMap();
	ID getID();

	void effectBattle();	//�퓬�ł̌���
	bool effectMap(std::shared_ptr<Player>);	//�}�b�v��ł̌���
	void draw_battle(int x, int y, int anime_frame);	//�o�g���ł̃A�j���[�V����
};