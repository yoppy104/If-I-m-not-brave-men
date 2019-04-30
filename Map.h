#pragma once
#include "NPC.h"
#include "Event.h"

//�}�b�v���̃N���X
class Map {
private:
	int		inf;			// ���̒n�_�������̏��
	bool	isMove;		// �ړ��\��
	bool	isEvent;		// �C�x���g�����邩�ǂ���
	bool	isNpc;			// npc�����邩�ǂ���
	bool	isEncount;		// �G���J�E���g���邩�ǂ���
	double	encountRate;	// �G�Ƃ̑�����
	int		encountTable;	// ���̏ꏊ�ŃG���J�E���g����G�̃e�[�u�����w�肷��id
	shared_ptr<NPC>	npc;			// ���̏ꏊ�ɂ���npc�̏��B
	shared_ptr<Event>	event;		// ���̏ꏊ�Ŕ�������C�x���g

public:
	//�R���X�g���N�^
	Map() = default;
	Map(int data, bool is_event, bool is_npc, int table, shared_ptr<NPC> npc);

	//�擾���\�b�h
	bool getIsMove() { return this->isMove && !this->isNpc; }
	bool getIsEvent() { return isEvent; }
	bool getIsNpc() { return isNpc; }
	bool getIsEncount() { return isEncount; }
	void setData(int data);
	void setIsEvent(bool is);
	void setNpc(bool isnt);
	void setNpc(shared_ptr<NPC> npc);
	shared_ptr<NPC> getNPC();
	void chatNPC();
	void setEvent(shared_ptr<Event> myevent);
	shared_ptr<Event> getEvent();
	void delEvent();
	void setTable(int table);
	double getRate() { return encountRate; }
	int getTable() { return encountTable; }
};