#pragma once

#include "Weapon.h"
#include "IDs.h"

class WoodSword :public Weapon {
public:
	WoodSword();
	virtual void drawAttackableArea(); //�U���\�G���A��`��
	virtual void selectAttack(); //�U���͈͂�I��
	virtual void drawAnimation(); //�U���A�j���[�V������`��
	virtual bool effectBattle(); //�퓬���̌��ʁA�^�U�l�Ŏg���邩��Ԃ�
	virtual bool effectMap();	 //�}�b�v���̌��ʁA�^�U�l�Ŏg���邩��Ԃ��B
};