#pragma once
#include "Item.h"

class Weapon : public Item{ // �����̍\����
	int point; // �ϓ�����l
	int weight; // �d�ʁB����ɂ���đ����ł����肪�ς��B
	int sound;
	
public:
	Weapon();
	Weapon(char name[], int id, bool is_sell, int point, int price, int weight, int sound, int image);

	//�p�����[�^���o���p�̊֐��Q
	int getPoint(); //���ʓ_���擾
	int getSound(); //���ʉ����擾

	//�퓬���ɌĂяo�����\�b�h
	virtual void drawAttackableArea(); //�U���\�G���A��`��
	virtual void selectAttack(); //�U���͈͂�I��
	virtual void drawAnimation(); //�U���A�j���[�V������`��
	virtual bool effectBattle(); //�퓬���̌���
	virtual bool effectMap();
};

