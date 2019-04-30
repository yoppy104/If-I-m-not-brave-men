#include "Inn.h"
#include "DxLib.h"
#include "M_Functions.h"

Inn::Inn(int pos_x, int pos_y, char name[], vector <string> text, int price, shared_ptr<PartyControl> pc) : NPC (pos_x, pos_y, name, text, 0){
	this->price = price;
	this->pc = pc;
	this->select_main = true;
	this->subwindow_image = LoadGraph("command.png");
	this->fade = 0;

	this->sounds.cancel = LoadSoundMem("SE_cancel.wav");
	this->sounds.enter = LoadSoundMem("SE_enter.wav");
	this->sounds.error = LoadSoundMem("SE_error.wav");
	this->sounds.move = LoadSoundMem("SE_move.wav");
	this->sounds.coin = LoadSoundMem("SE_coin_2.wav");
	this->sounds.heal = LoadSoundMem("SE_heal.wav");
	ChangeVolumeSoundMem(200, this->sounds.heal);
	this->sounds.yado = LoadSoundMem("SE_Yado.wav");
}

bool Inn::chat() {
	DrawExtendGraph(100, 800, 1860, 1000, this->text_box, TRUE);
	this->getName(150, 810);
	if (this->step == 1) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), this->text[this->step].c_str(),this->price * pc->getNumMember());
		DrawExtendGraph(1650, 50, 1900, 350, this->subwindow_image, TRUE);
		DrawFormatString(1700, 100, GetColor(0, 0, 0), "������");
		DrawFormatString(1700, 200, GetColor(0, 0, 0), "%d�M��", pc->getNumCoin());
		DrawExtendGraph(1600, 700, 1800, 800, this->subwindow_image, TRUE);
		DrawFormatString(1660, 715, GetColor(0, 0, 0), "�͂�");
		DrawFormatString(1650, 755, GetColor(0, 0, 0), "������");
		DrawLine(1650, 750 + 40 * !this->select_main, 1755, 750 + 40 * !this->select_main, GetColor(0, 0, 0), 5);
		if (Button(KEY_INPUT_UP) == 1) {
			if (!this->select_main) {
				PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
				this->select_main = !this->select_main;
			}
			else{
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) == 1) {
			if (this->select_main) {
				PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
				this->select_main = !this->select_main;
			}
			else{
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			if (this->select_main) {
				shared_ptr<Player> temp = pc->getMember(0);
				temp->healHp();
				temp->plusMp();
				pc->addNumCoin(-1 * this->price * pc->getNumMember());
				this->step = -1;
			}
			else {
				this->step += 2;
			}
		}
		else if (Button(KEY_INPUT_B) == 1) {
			PlaySoundMem(this->sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
			return true;
		}
	}
	else if (this->step == -1) {
		PlaySoundMem(this->sounds.yado, DX_PLAYTYPE_BACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 16 * this->fade);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		DrawFormatString(700, 540, GetColor(255, 255, 255), "�A�����B�͂�������Ƌx�����Ƃ����B");
		this->fade += 1;
		if (this->fade == 16) {
			this->step = -2;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (this->step == -2) {
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		DrawFormatString(700, 540, GetColor(255, 255, 255), "�A�����B�͂�������Ƌx�����Ƃ����B");
		if (Button(KEY_INPUT_SPACE) == 1 && !CheckSoundMem(this->sounds.yado)){
			this->step = -3;
		}
	}
	else if (this->step == -3) {
		PlaySoundMem(this->sounds.heal, DX_PLAYTYPE_BACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 16 * this->fade);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		DrawFormatString(700, 540, GetColor(255, 255, 255), "�A�����B�͂�������Ƌx�����Ƃ����B");
		this->fade -= 1;
		if (this->fade == 0) {
			this->step = 2;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else {
		DrawFormatString(150, 850, GetColor(0, 0, 0), this->text[this->step].c_str());
		if (Button(KEY_INPUT_SPACE) == 1) {
			if (this->step == this->text.size() - 1) {
				this->step = 0;
				this->select_main = true;
				return true;
			}
			this->step++;
		}
	}
	return false;
}