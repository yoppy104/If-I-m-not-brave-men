#include "Event.h"
#include "M_Functions.h"
#include "DxLib.h"
#include "IDs.h"

Event::Event(int id) {
	this->id = id;
	this->step = 0;
	switch (id) {
	case HAJITO:
		this->text.push_back("ここがハジート村かあ");
		this->text.push_back("ここには幼馴染のリリィが住んでるんだよなあ");
		break;
	case TEATURE:
		this->text.push_back("ここは俺の魔術の先生のところだな。");
		this->text.push_back("俺は勇者で魔力を持つ数少ない人間だから魔術を勉強できるのは重要だな。");
		break;
	case HILBATE:
		this->text.push_back("ここは軍国主義の国、ヒルベート。");
		this->text.push_back("ここの王様はたいそうな野望をもっているらしいな。");
		break;
	case HOUSE:
		this->text.push_back("ここは俺とアルクが住んでいる家だな。");
		this->text.push_back("アルクは手厳しいからなあ。いっつも修行と称して俺をボコしやがる。");
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
	DrawFormatString(120, 825, GetColor(0, 0, 0), "アレン");
	DrawFormatString(150, 900, GetColor(0, 0, 0), this->text[this->step]);
	if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
		this->step += 1;
		
	}
	return false;
}