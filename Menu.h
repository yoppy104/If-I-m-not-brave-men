#pragma once
#include "PartyControl.h"

class Menu {
private:
	int mode;			//���[�h
						/*
						0 : main
						1 : item
						2 : equipment
						3 : magic
						4 : save
						5 : close
						*/
	int main_select;	//���C���ł̑I��������肷��ϐ�
	int item_select;	//�A�C�e���ł̑I��������肷��ϐ�
	int equipment_select; //�����ł̑I��������肷��ϐ�
	int magic_select;	//���p�ł̑I��������肷��ϐ�
	int save_select;	//�Z�[�u�ł̑I��������肷��ϐ�
	int step;			//�`��p��step�ϐ�
	int window_image;	//�E�B���h�E�̉摜
	int pointer_image;	//�|�C���^�[�̉摜
	int subwindw_image;
	int start;
	int sub_select;
	
	PartyControl* pc;

	int sound_enter;
	int sound_error;
	int sound_move;
	int sound_cancel;

public:
	Menu();
	Menu(PartyControl* p);
	bool Update();			//�S�̂̍X�V
	bool updateMain();		//���C��
	bool updateItem();		//�A�C�e��
	bool updateEquipment();	//����
	bool updateMagic();		//���p
	bool updateSave();		//�Z�[�u
	bool closeWindow();		//�E�B���h�E�����
};