#pragma once
#include "Npc.h"
#include "PartyControll.h"

/*
�T�v :	�h���̃N���X
*/

class Inn : public NPC {
private:
	using Sound = struct {
		int enter;
		int error;
		int move;
		int cancel;
		int coin;
		int heal;
		int yado;
	};

	int price;	//�h����
	std::shared_ptr<PartyControll> pc;
	int subwindow_image;	//�͂��A�������̍��ڂ�\������E�B���h�E
	bool select_main;		//�͂��A��������I������J�[�\��
	int fade;

	Sound sounds;

public:
	Inn(int pos_x, int pos_y, char name[], std::vector <std::string> text, int price, std::shared_ptr<PartyControll> pc);
	bool chat();
};