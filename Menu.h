#pragma once

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
	int step;			//�`��p��step�ϐ�
	int window_image;	//�E�B���h�E�̉摜
	int pointer_image;	//�|�C���^�[�̉摜
	

public:
	Menu();
	bool Update();			//�S�̂̍X�V
	bool updateMain();		//���C��
	bool updateItem();		//�A�C�e��
	bool updateEquipment();	//����
	bool updateMagic();		//���p
	bool updateSave();		//�Z�[�u
	bool closeWindow();		//�E�B���h�E�����
};