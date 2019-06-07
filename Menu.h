#pragma once
#include "PartyControl.h"
#include "IDs.h"

enum Mode {
	MAIN,
	ITEM,
	EQUIPMENT,
	MAGIC,
	SAVE,
	CLOSE
};

class Menu {
private:
	using Image = struct {
		int window;
		int pointer;
		int subwindow;
	};

	using Sound = struct {
		int enter;
		int error;
		int move;
		int cancel;
	};

	Mode mode;
	int mainSelect;	//���C���ł̑I��������肷��ϐ�
	int itemSelect;	//�A�C�e���ł̑I��������肷��ϐ�
	int equipmentSelect; //�����ł̑I��������肷��ϐ�
	int magicSelect;	//���p�ł̑I��������肷��ϐ�
	int saveSelect;	//�Z�[�u�ł̑I��������肷��ϐ�
	int step;			//�`��p��step�ϐ�
	Image images;
	int start;
	int subSelect;
	
	std::weak_ptr<PartyControl> pc;

	Sound sounds;

public:
	Menu() = default;
	Menu(std::shared_ptr<PartyControl> p);
	bool Update();			//�S�̂̍X�V
	bool updateMain();		//���C��
	bool updateItem();		//�A�C�e��
	bool updateEquipment();	//����
	bool updateMagic();		//���p
	bool updateSave();		//�Z�[�u
	bool closeWindow();		//�E�B���h�E�����
};