#pragma once
#include "NPC.h"

//�}�b�v���̃N���X
class Map {
private:
	int		inf;			// ���̒n�_�������̏��
	bool	is_move;		// �ړ��\��
	bool	is_event;		// �C�x���g�����邩�ǂ���
	bool	is_npc;			// npc�����邩�ǂ���
	bool	is_encount;		// �G���J�E���g���邩�ǂ���
	double	encount_rate;	// �G�Ƃ̑�����
	int		encount_table;	// ���̏ꏊ�ŃG���J�E���g����G�̃e�[�u�����w�肷��id
	NPC		npc;			// ���̏ꏊ�ɂ���npc�̏��B

public:
	//�R���X�g���N�^
	Map();
	Map(int data, bool is_event, bool is_npc, int table, NPC npc);

	//�擾���\�b�h
	bool getIsMove();
	bool getIsEvent();
	bool getIsNpc();
	bool getIsEncount();
	void setData(int data);
	void setIsEvent(bool is);
	void setNpc(bool isnt);
	void setNpc(NPC* npc);
	void setTable(int table);
	double getRate();
	int getTable();
};