#include "Event.h"
#include "M_Functions.h"
#include "DxLib.h"
#include "IDs.h"

Event::Event(int id) {
	id = id;
	step = 0;
	switch (id) {
	case HAJITO:
		text.push_back("�������n�W�[�g������");
		text.push_back("�����ɂ͗c����̃����B���Z��ł�񂾂�Ȃ�");
		break;
	case TEATURE:
		text.push_back("�����͉��̖��p�̐搶�̂Ƃ��낾�ȁB");
		text.push_back("���͗E�҂Ŗ��͂��������Ȃ��l�Ԃ����疂�p��׋��ł���̂͏d�v���ȁB");
		break;
	case HILBATE:
		text.push_back("�����͌R����`�̍��A�q���x�[�g�B");
		text.push_back("�����̉��l�͂��������Ȗ�]�������Ă���炵���ȁB");
		break;
	case HOUSE:
		text.push_back("�����͉��ƃA���N���Z��ł���Ƃ��ȁB");
		text.push_back("�A���N�͎茵��������Ȃ��B�������C�s�Ə̂��ĉ����{�R���₪��B");
		break;
	}

	text_box = LoadGraph("window.png");
	sound_enter = LoadSoundMem("SE_enter.wav");
}

bool Event::Update() {
	if (step == text.size()) {
		return true;
	}
	DrawExtendGraph(100, 800, 1860, 1000, text_box, TRUE);
	DrawFormatString(120, 825, GetColor(0, 0, 0), "�A����");
	DrawFormatString(150, 900, GetColor(0, 0, 0), text[step]);
	if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(sound_enter, DX_PLAYTYPE_BACK, TRUE);
		step += 1;
		
	}
	return false;
}