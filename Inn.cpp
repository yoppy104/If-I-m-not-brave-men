#include "Inn.h"
#include "DxLib.h"
#include "M_Functions.h"

Inn::Inn(int pos_x, int pos_y, char name[], vector <char*> text, int price, PartyControl* pc) : NPC (pos_x, pos_y, name, text){
	this->price = price;
	this->pc = pc;
	this->select_main = true;
	this->subwindow_image = LoadGraph("command.png");
	this->fade = 0;
}

bool Inn::chat() {
	DrawExtendGraph(100, 800, 1860, 1000, this->text_box, TRUE);
	this->getName(150, 810);
	if (this->step == 1) {
		DrawFormatString(150, 850, GetColor(255, 255, 255), this->text[this->step],this->price * pc->getNumMember());
		DrawExtendGraph(1600, 700, 1800, 800, this->subwindow_image, TRUE);
		DrawFormatString(1660, 715, GetColor(0, 0, 0), "はい");
		DrawFormatString(1650, 755, GetColor(0, 0, 0), "いいえ");
		DrawLine(1650, 750 + 40 * !this->select_main, 1755, 750 + 40 * !this->select_main, GetColor(0, 0, 0), 5);
		if (Button(KEY_INPUT_UP) == 1) {
			if (!this->select_main) {
				this->select_main = !this->select_main;
			}
		}
		else if (Button(KEY_INPUT_DOWN) == 1) {
			if (this->select_main) {
				this->select_main = !this->select_main;
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			if (this->select_main) {
				Player* temp = pc->getMember(0);
				temp->healHp();
				temp->plusMp();
				pc->addNumCoin(this->price * pc->getNumMember());
				this->step = -1;
			}
			else {
				this->step++;
			}
		}
		else if (Button(KEY_INPUT_B) == 1) {
			return true;
		}
	}
	else if (this->step == -1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 16 * this->fade);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		DrawFormatString(700, 540, GetColor(255, 255, 255), "アレン達はしっかりと休息をとった。");
		this->fade += 1;
		if (this->fade == 16) {
			this->step = -2;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (this->step == -2) {
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		DrawFormatString(700, 540, GetColor(255, 255, 255), "アレン達はしっかりと休息をとった。");
		if (Button(KEY_INPUT_SPACE) == 1){
			this->step = -3;
		}
	}
	else if (this->step == -3) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 16 * this->fade);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		DrawFormatString(700, 540, GetColor(255, 255, 255), "アレン達はしっかりと休息をとった。");
		this->fade -= 1;
		if (this->fade == 0) {
			this->step = 2;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else {
		DrawFormatString(150, 850, GetColor(0, 0, 0), this->text[this->step]);
		if (Button(KEY_INPUT_SPACE) == 1) {
			if (this->step == this->text.size() - 1) {
				this->step = 0;
				return true;
			}
			this->step++;
		}
	}
	return false;
}