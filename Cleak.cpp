#include "Cleark.h"
#include "DxLib.h"
#include "M_Functions.h"

Cleark::Cleark() {

}

Cleark::Cleark(char name[], int x, int y, vector<shared_ptr<Item>> item, vector<string> text, shared_ptr<PartyControl> pc) : NPC(x, y, name, text, 2) {
	this->items = item;
	this->start = 0;
	this->num = -1;
	this->window_image = LoadGraph("menu.png");
	this->subwindow_image = LoadGraph("command.png");
	this->pointer_image = LoadGraph("pointer.png");
	this->select_main = 0;
	this->select_sub = -1;
	this->select_sell = -1;
	this->pc = pc;

	this->sound_coin = LoadSoundMem("SE_coin_2.wav");
	this->sound_enter = LoadSoundMem("SE_enter.wav");
	this->sound_error = LoadSoundMem("SE_error.wav");
	this->sound_move = LoadSoundMem("SE_move.wav");
	this->sound_cancel = LoadSoundMem("SE_cancel.wav");
}

int Cleark::update() {
	DrawExtendGraph(50, 50, 868, 612, this->window_image, TRUE);
	DrawExtendGraph(1650, 50, 1900, 350, this->subwindow_image, TRUE);
	DrawFormatString(1700, 100, GetColor(0, 0, 0), "所持金");
	DrawFormatString(1700, 200, GetColor(0, 0, 0), "%dギル", pc->getNumCoin());
	DrawFormatString(100, 100, GetColor(0, 0, 0), "買う");
	DrawFormatString(100, 150, GetColor(0, 0, 0), "売る");
	DrawFormatString(100, 200, GetColor(0, 0, 0), "やめる");
	DrawLine(70, 130 + 50 * this->select_main, 250, 130 + 50 * this->select_main, GetColor(0, 0, 0), 5);

	if (this->num != -1) {
		return this->buy();
	}
	else if (this->select_sell != -1) {
		return this->sell();
	}
	else if (this->select_sub == -1) {
		if (Button(KEY_INPUT_UP) % 15 == 1) {
			if (this->select_main - 1 >= 0) {
				PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
				this->select_main--;
			}
			else{
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if (this->select_main + 1 < 3) {
				PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
				this->select_main++;
			}
			else{
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_B) == 1) {
			PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
			return 2;
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
			if (this->select_main == 0) {
				this->select_sub = 0;
			}
			else if (this->select_main == 1) {
				if (this->pc->getNumItem() != 0) {
					this->select_sub = 0;
				}
				else {
					return 4;
				}
			}
			else {
				this->select_main = 0;
				this->select_sell = -1;
				this->select_sub = -1;
				return 2;
			}
		}
	}
	else {
		switch (this->select_main) {
		case 0:
			for (int i = 0; i < this->items.size(); i++) {
				this->items[i]->getName(400, 100 + 50 * i);
				DrawFormatString(650, 100 + 50 * i, GetColor(0, 0, 0), "%dギル", this->items[i]->getPriceBuy());
			}
			DrawLine(390, 130 + 50 * this->select_sub, 800, 130 + 50 * this->select_sub, GetColor(0, 0, 0), 5);
			if (Button(KEY_INPUT_UP) % 15 == 1) {
				if (this->select_sub - 1 >= 0) {
					PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
					this->select_sub--;
				}
				else{
					PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
				if (this->select_sub + 1 < this->items.size()) {
					PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
					this->select_sub++;
				}
				else{
					PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_SPACE) == 1) {
				PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
				this->num = 1;
			}
			else if (Button(KEY_INPUT_B) == 1) {
				PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
				this->select_sub = -1;
			}
			break;
		case 1:
			int end;
			if (pc->getNumItem() < 10 || pc->getNumItem() < this->start + 10) {
				end = pc->getNumItem();
			}
			else {
				end = this->start + 10;
			}
			for (int i = this->start; i < end; i++) {
				pc->getItem(i)->getName(400, 100 + 50 * i);
			}
			DrawLine(390, 130 + 50 * this->select_sub, 800, 130 + 50 * this->select_sub, GetColor(0, 0, 0), 5);
			if (Button(KEY_INPUT_UP) % 15 == 1) {
				if (this->select_sub - 1 >= 0) {
					PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
					this->select_sub--;
					if (this->select_sub < this->start) {
						this->start--;
					}
				}
				else{
					PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
				if (this->select_sub + 1 < pc->getNumItem()) {
					PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
					this->select_sub++;
					if (this->select_sub > this->start + 9) {
						this->start++;
					}
				}
				else{
					PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_SPACE) == 1) {
				PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
				if (pc->getItem(this->select_sub)->getIsSell()) {
					this->select_sell = 0;
				}
				else {
					return 5;
				}
			}
			else if (Button(KEY_INPUT_B) == 1) {
				PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
				this->select_sub = -1;
			}
			break;
		}
	}
	return 0;
}

int Cleark::buy() {
	unsigned int col = GetColor(0, 0, 0);
	DrawExtendGraph(800, 500, 1100, 800, this->subwindow_image, TRUE);
	DrawFormatString(900, 520, col, "何個");
	DrawFormatString(945, 550, col, "↑");
	DrawFormatString(940, 650, col, "%d",this->num);
	DrawFormatString(945, 750, col, "↓");
	if (Button(KEY_INPUT_UP) % 15 == 1) {
		PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
		this->num++;
	}
	else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
		if (this->num - 1 >= 1) {
			PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
			this->num--;
		}
		else{
			PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_RIGHT) % 15 == 1) {
		PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
		this->num += 10;
	}
	else if (Button(KEY_INPUT_LEFT) % 15 == 1) {
		if (this->num - 10 >= 1) {
			PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
			this->num -= 10;
		}
		else {
			PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			this->num = 10;
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
		int price = this->items[this->select_sub]->getPriceBuy() * this->num;
		if (this->pc->getNumCoin() < price) {
			this->num = -1;
			return 3;
		}
		else {
			this->pc->addNumCoin(-1 * price);
			for (int i = 0; i < this->num; i++) {
				this->pc->addItem(this->items[this->select_sub]);
			}
			this->num = -1;
			return 1;
		}
	}
	else if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
		this->num = -1;
	}
	return 0;
}

int Cleark::sell() {
	DrawExtendGraph(800, 500, 1100, 800, this->subwindow_image, TRUE);
	DrawFormatString(150, 850, GetColor(0, 0, 0), "それなら%dギルで買い取ります。",this->pc->getItem(this->select_sub)->getPriceSell());
	DrawFormatString(900, 550, GetColor(0, 0, 0), "売ります");
	DrawFormatString(900, 650, GetColor(0, 0, 0), "はい");
	DrawFormatString(900, 700, GetColor(0, 0, 0), "いいえ");
	DrawLine(890, 680 + 50 * this->select_sell, 1000, 680 + 50 * this->select_sell, GetColor(0, 0, 0), 5);
	if (Button(KEY_INPUT_UP) % 15 == 1) {
		if (this->select_sell - 1 >= 0) {
			PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
			this->select_sell--;
		}
		else{
			PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
		if (this->select_sell + 1 < 2) {
			PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
			this->select_sell++;
		}
		else{
			PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(this->sound_coin, DX_PLAYTYPE_BACK, TRUE);
		if (this->select_sell == 0) {
			int price = this->pc->getItem(this->select_sub)->getPriceSell();
			this->pc->delItem(this->select_sub);
			this->pc->addNumCoin(price);
			this->select_sell = -1;
			return 1;
		}
		else {
			this->select_sell = -1;
		}
	}
	else if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
		this->select_sell = -1;
	}
	return 0;
}

bool Cleark::chat() {
	DrawExtendGraph(100, 800, 1860, 1000, this->text_box, TRUE);
	this->getName(150, 810);
	if (this->step == 1) {
		int test = this->update();
		if (test == 1) {
			this->step++;
		}
		else if (test == 2) {
			this->step = -1;
		}
		else if (test == 3) {
			this->step = -2;
		}
		else if (test == 4) {
			this->step = -3;
		}
		else if (test == 5) {
			this->step = -4;
		}
	}
	else if (this->step == -1) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), "また来てください。");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
			this->step = 0;
			return true;
		}
	}
	else if (this->step == -2) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), "お金が足りませんよ。");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
			this->step = 0;
			this->select_main = 0;
			this->select_sub = -1;
			this->select_sell = -1;
			this->num = -1;
			return true;
		}
	}
	else if (this->step == -3) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), "アイテムを所持していませんよ。");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
			this->step = 0;
			this->select_main = 0;
			this->select_sub = -1;
			this->select_sell = -1;
			this->num = -1;
			return true;
		}
	}
	else if (this->step == -4) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), "それは買い取れませんよ。");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
			this->step = 0;
			this->select_main = 0;
			this->select_sub = -1;
			this->select_sell = -1;
			this->num = -1;
			return true;
		}
	}
	else {
  		if (this->text[this->step] != "") {
			DrawFormatString(150, 850, GetColor(0, 0, 0), this->text[this->step].c_str());
		}
		else {
			this->step++;
			return false;
		}
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sound_coin, DX_PLAYTYPE_BACK, TRUE);
			if (this->step == this->text.size() - 1) {
				this->step = 0;
				this->select_main = 0;
				this->select_sub = -1;
				this->select_sell = -1;
				this->num = -1;
				return true;
			}
			this->step++;
		}
	}
	return false;
}