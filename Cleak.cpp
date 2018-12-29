#include "Cleark.h"
#include "DxLib.h"
#include "M_Functions.h"

Cleark::Cleark() {

}

Cleark::Cleark(char name[], int x, int y, vector<Item*> item, vector<char*> text, PartyControl* pc) : NPC(x, y, name, text) {
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
}

int Cleark::update() {
	DrawExtendGraph(50, 50, 868, 612, this->window_image, TRUE);
	DrawFormatString(100, 100, GetColor(0, 0, 0), "買う");
	DrawFormatString(100, 150, GetColor(0, 0, 0), "売る");
	DrawFormatString(100, 200, GetColor(0, 0, 0), "やめる");
	DrawGraph(75, 100 + 50 * this->select_main, this->pointer_image, TRUE);

	if (this->num != -1) {
		return this->buy();
	}
	else if (this->select_sell != -1) {
		return this->sell();
	}
	else if (this->select_sub == -1) {
		if (Button(KEY_INPUT_UP) % 15 == 1) {
			if (this->select_main - 1 >= 0) {
				this->select_main--;
			}
		}
		else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if (this->select_main + 1 < 3) {
				this->select_main++;
			}
		}
		else if (Button(KEY_INPUT_B) == 1) {
			return 2;
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
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
			DrawGraph(350, 100 + 50 * this->select_sub, this->pointer_image, TRUE);
			if (Button(KEY_INPUT_UP) % 15 == 1) {
				if (this->select_sub - 1 >= 0) {
					this->select_sub--;
				}
			}
			else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
				if (this->select_sub + 1 < this->items.size()) {
					this->select_sub++;
				}
			}
			else if (Button(KEY_INPUT_SPACE) == 1) {
				this->num = 1;
			}
			else if (Button(KEY_INPUT_B) == 1) {
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
			DrawGraph(350, 100 + 50 * this->select_sub, this->pointer_image, TRUE);
			if (Button(KEY_INPUT_UP) % 15 == 1) {
				if (this->select_sub - 1 >= 0) {
					this->select_sub--;
					if (this->select_sub < this->start) {
						this->start--;
					}
				}
			}
			else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
				if (this->select_sub + 1 < pc->getNumItem()) {
					this->select_sub++;
					if (this->select_sub > this->start + 9) {
						this->start++;
					}
				}
			}
			else if (Button(KEY_INPUT_SPACE) == 1) {
				if (pc->getItem(this->select_sub)->getIsSell()) {
					this->select_sell = 0;
				}
				else {
					return 5;
				}
			}
			else if (Button(KEY_INPUT_B) == 1) {
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
		this->num++;
	}
	else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
		if (this->num - 1 >= 1) {
			this->num--;
		}
	}
	else if (Button(KEY_INPUT_RIGHT) % 15 == 1) {
		this->num += 10;
	}
	else if (Button(KEY_INPUT_LEFT) % 15 == 1) {
		if (this->num - 10 >= 1) {
			this->num = 10;
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
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
		this->num = -1;
	}
	return 0;
}

int Cleark::sell() {
	DrawExtendGraph(800, 500, 1100, 800, this->subwindow_image, TRUE);
	DrawFormatString(900, 550, GetColor(0, 0, 0), "売ります");
	DrawFormatString(950, 650, GetColor(0, 0, 0), "はい");
	DrawFormatString(950, 700, GetColor(0, 0, 0), "いいえ");
	DrawGraph(900, 650 + 50 * this->select_sell, this->pointer_image, TRUE);
	if (Button(KEY_INPUT_UP) % 15 == 1) {
		if (this->select_sell - 1 >= 0) {
			this->select_sell--;
		}
	}
	else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
		if (this->select_sell + 1 < 2) {
			this->select_sell++;
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
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
			this->step = 0;
			return true;
		}
	}
	else if (this->step == -2) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), "お金が足りませんよ。");
		if (Button(KEY_INPUT_SPACE) == 1) {
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
			DrawFormatString(150, 850, GetColor(0, 0, 0), this->text[this->step]);
		}
		else {
			this->step++;
			return false;
		}
		if (Button(KEY_INPUT_SPACE) == 1) {
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