#pragma once

#include <iostream>

using namespace std;

class Equipment{ // �����̍\����
	int type; // 0:����, 1:��, 2:��, 3:��, 4:�A�N�Z�T���[
	int point; // �ϓ�����l
	int price; // �w�����̒l�i
	int weight; // �d�ʁB����ɂ���đ����ł����肪�ς��B
	int attackable;//���S�~�͈̔́A-1�̎��͑S�͈�
	int attack_area;//�U���͈�
	/*
	�U���͈͈͂ȉ��̗l�ɒ�`����B
	10�̈ʂ�
	1��1�}�X
	2�͏c�����A1�̈ʂŒ������`
	3�͉������A1�̈ʂŒ������`
	4�͓��S�~�A1�̈ʂŔ��a���`
	�΂ߕ����̍U���͒�`���Ȃ�
	*/
	
public:
	Equipment();
	Equipment(int type, int point, int price, int weight, int attackable, int attack_area);

	//�p�����[�^���o���p�̊֐��Q
	int getAttackable();
};

