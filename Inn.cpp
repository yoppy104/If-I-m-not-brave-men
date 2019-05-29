#include "Inn.h"
#include "DxLib.h"
#include "M_Functions.h"

Inn::Inn(int pos_x, int pos_y, char name[], vector <string> text, int price, std::shared_ptr<PartyControl> pc) : NPC (pos_x, pos_y, name, text, 0){
	price = price;
	pc = pc;
	select_main = true;
	subwindow_image = LoadGraph("image/command.png");
	fade = 0;

	sounds.cancel = LoadSoundMem("sounds\\SE_cancel.wav");
	sounds.enter = LoadSoundMem("sounds\\SE_enter.wav");
	sounds.error = LoadSoundMem("sounds\\SE_error.wav");
	sounds.move = LoadSoundMem("sounds\\SE_move.wav");
	sounds.coin = LoadSoundMem("sounds\\SE_coin_2.wav");
	sounds.heal = LoadSoundMem("sounds\\SE_heal.wav");
	ChangeVolumeSoundMem(200, sounds.heal);
	sounds.yado = LoadSoundMem("sounds\\SE_Yado.wav");
}

bool Inn::chat() {
	DrawExtendGraph(100, 800, 1860, 1000, text_box, TRUE);
	getName(150, 810);
	if (step == 1) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), text[step].c_str(),price * pc->getNumMember());
		DrawExtendGraph(1650, 50, 1900, 350, subwindow_image, TRUE);
		DrawFormatString(1700, 100, GetColor(0, 0, 0), "所持金");
		DrawFormatString(1700, 200, GetColor(0, 0, 0), "%dギル", pc->getNumCoin());
		DrawExtendGraph(1600, 700, 1800, 800, subwindow_image, TRUE);
		DrawFormatString(1660, 715, GetColor(0, 0, 0), "はい");
		DrawFormatString(1650, 755, GetColor(0, 0, 0), "いいえ");
		DrawLine(1650, 750 + 40 * !select_main, 1755, 750 + 40 * !select_main, GetColor(0, 0, 0), 5);
		if (Button(KEY_INPUT_UP) == 1) {
			if (!select_main) {
				PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
				select_main = !select_main;
			}
			else{
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) == 1) {
			if (select_main) {
				PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
				select_main = !select_main;
			}
			else{
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			if (select_main) {
				std::shared_ptr<Player> temp = pc->getMember(0);
				temp->healHp();
				temp->plusMp();
				pc->addNumCoin(-1 * price * pc->getNumMember());
				step = -1;
			}
			else {
				step += 2;
			}
		}
		else if (Button(KEY_INPUT_B) == 1) {
			PlaySoundMem(sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
			return true;
		}
	}
	else if (step == -1) {
		PlaySoundMem(sounds.yado, DX_PLAYTYPE_BACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 16 * fade);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		DrawFormatString(700, 540, GetColor(255, 255, 255), "アレン達はしっかりと休息をとった。");
		fade += 1;
		if (fade == 16) {
			step = -2;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (step == -2) {
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		DrawFormatString(700, 540, GetColor(255, 255, 255), "アレン達はしっかりと休息をとった。");
		if (Button(KEY_INPUT_SPACE) == 1 && !CheckSoundMem(sounds.yado)){
			step = -3;
		}
	}
	else if (step == -3) {
		PlaySoundMem(sounds.heal, DX_PLAYTYPE_BACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 16 * fade);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		DrawFormatString(700, 540, GetColor(255, 255, 255), "アレン達はしっかりと休息をとった。");
		fade -= 1;
		if (fade == 0) {
			step = 2;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else {
		DrawFormatString(150, 850, GetColor(0, 0, 0), text[step].c_str());
		if (Button(KEY_INPUT_SPACE) == 1) {
			if (step == text.size() - 1) {
				step = 0;
				select_main = true;
				return true;
			}
			step++;
		}
	}
	return false;
}