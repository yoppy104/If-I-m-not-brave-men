#include "Event.h"
#include "M_Functions.h"
#include "DxLib.h"
#include "IDs.h"

Event::Event(int id) {
	this->id = id;
	this->step = 0;
	switch (id) {
	case HAJITO:
		this->text.push_back("�������n�W�[�g������");
		this->text.push_back("�����ɂ͗c����̃����B���Z��ł�񂾂�Ȃ�");
		break;
	case TEATURE:
		this->text.push_back("�����͉��̖��p�̐搶�̂Ƃ��낾�ȁB");
		this->text.push_back("���͗E�҂Ŗ��͂��������Ȃ��l�Ԃ����疂�p��׋��ł���̂͏d�v���ȁB");
		break;
	case HILBATE:
		this->text.push_back("�����͌R����`�̍��A�q���x�[�g�B");
		this->text.push_back("�����̉��l�͂��������Ȗ�]�������Ă���炵���ȁB");
		break;
	case HOUSE:
		this->text.push_back("�����͉��ƃA���N���Z��ł���Ƃ��ȁB");
		this->text.push_back("�A���N�͎茵��������Ȃ��B�������C�s�Ə̂��ĉ����{�R���₪��B");
		break;
	}

	this->text_box = LoadGraph("window.png");
	this->sound_enter = LoadSoundMem("SE_enter.wav");
}

bool Event::Update() {
	if (this->step == this->text.size()) {
		return true;
	}
	DrawExtendGraph(100, 800, 1860, 1000, this->text_box, TRUE);
	DrawFormatString(120, 825, GetColor(0, 0, 0), "�A����");
	DrawFormatString(150, 900, GetColor(0, 0, 0), this->text[this->step]);
	if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
		this->step += 1;
		
	}
	return false;
}