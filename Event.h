#pragma once
#include <vector>

/*
�T�v :	�C�x���g��������������Base�N���X
		�p�����Ďg�p����\��
*/

class Event {
protected:
	int id;		//�C�x���gID
	int step;	//�C�x���g�A�j���[�V�����p�̃t���[����
	std::vector <char*> text;	//�C�x���g�̃e�L�X�g

	int text_box;		//�e�L�X�g��\�����镔���̉摜
	int sound_enter;	//�����𑗂����Ƃ��̉�

public:
	Event() = default;
	Event(int id);
	virtual bool Update();
};