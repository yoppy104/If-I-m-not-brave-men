#include "Event.h"
#include "M_Functions.h"
#include "DxLib.h"
#include "IDs.h"

Event::Event(int id) {
	id = id;
	step = 0;
	switch (id) {
	case HAJITO:
		text.push_back("ここがハジート村かあ");
		text.push_back("ここには幼馴染のリリィが住んでるんだよなあ");
		break;
	case TEATURE:
		text.push_back("ここは俺の魔術の先生のところだな。");
		text.push_back("俺は勇者で魔力を持つ数少ない人間だから魔術を勉強できるのは重要だな。");
		break;
	case HILBATE:
		text.push_back("ここは軍国主義の国、ヒルベート。");
		text.push_back("ここの王様はたいそうな野望をもっているらしいな。");
		break;
	case HOUSE:
		text.push_back("ここは俺とアルクが住んでいる家だな。");
		text.push_back("アルクは手厳しいからなあ。いっつも修行と称して俺をボコしやがる。");
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
	DrawFormatString(120, 825, GetColor(0, 0, 0), "アレン");
	DrawFormatString(150, 900, GetColor(0, 0, 0), text[step]);
	if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(sound_enter, DX_PLAYTYPE_BACK, TRUE);
		step += 1;
		
	}
	return false;
}