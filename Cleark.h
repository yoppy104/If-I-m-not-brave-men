#pragma once
#include "Npc.h"
#include "Item.h"
#include "IDs.h"
#include <vector>
#include "PartyControll.h"
#include <string>

/*
�T�v :	�X���p�̃N���X�B
		���퉮�A�h��A����͋�ʂ��Ȃ�
*/

class Cleark : public NPC {
private:
	using Image = struct {
		int window;
		int subWindow;
		int pointer;
	};

	using Sound = struct {
		int enter;
		int error;
		int move;
		int coin;
		int cancel;
	};

	std::vector <ID> items;			//�A�C�e����ID�B���ۂɎ󂯓n������
	std::vector <Item> itemsInf;	//�A�C�e���̏����o�͂��邽�߂̂���

	int start;

	int select_main;	//��I��
	int select_sub;		//�͂��A�������̑I��
	int select_sell;	//���p����Ƃ��̃A�C�e���I���J�[�\��

	bool is_buy;

	bool is_select_value;
	int selected_value;

	std::shared_ptr<PartyControll> pc;

	Image image;

	Sound sound;

public:
	Cleark() = default;
	Cleark(std::string name, int x, int y, std::vector<ID> item, std::vector<std::string> text, std::shared_ptr<PartyControll> pc);
	int update();
	int sell(); //�v���C���[������
	int buy(); //�v���C���[������
	bool chat();

	bool SelectValue(int max_value);
};