#include "M_Functions.h"
#include "Menu.h"
#include "DxLib.h"
#include <fstream>
#include "Magic.h"

using namespace std;

Menu::Menu() {
	this->mode = 0;
	this->step = 5;
	this->main_select = 1;
	this->item_select = 0;
	this->equipment_select = 0;
	this->magic_select = 0;
	this->save_select = 0;
	this->window_image = LoadGraph("menu.png");
	this->pointer_image = LoadGraph("pointer.png");
	this->subwindw_image = LoadGraph("command.png");
	this->start = 0;
	this->sub_select = -1;
}

Menu::Menu(PartyControl* p) {
	this->mode = 0;
	this->step = 5;
	this->main_select = 1;
	this->item_select = 0;
	this->equipment_select = 0;
	this->magic_select = 0;
	this->save_select = 0;
	this->pc = p;
	this->window_image = LoadGraph("menu.png");
	this->pointer_image = LoadGraph("pointer.png");
	this->subwindw_image = LoadGraph("command.png");
	this->start = 0;
	this->sub_select = -1;
}

bool Menu::Update() {
	if (this->step <= 0) {
		DrawExtendGraph(50, 50, 868, 612, this->window_image, TRUE);
		DrawFormatString(125, 100, GetColor(0, 0, 0), "アイテム");
		DrawFormatString(125, 200, GetColor(0, 0, 0), "装備");
		DrawFormatString(125, 300, GetColor(0, 0, 0), "魔術");
		DrawFormatString(125, 400, GetColor(0, 0, 0), "セーブ");
		switch (this->mode) {
		case 0:
			return this->updateMain();
			break;
		case 1:
			return this->updateItem();
			break;
		case 2:
			return this->updateEquipment();
			break;
		case 3:
			return this->updateMagic();
			break;
		case 4:
			return this->updateSave();
			break;
		case 5:
			return this->closeWindow();
			break;
		}
	}
	else {
		// メニュー画面の開閉処理
		//w 242 h 178
		DrawExtendGraph(242 - 192 / this->step, 178 - 126 / this->step, 242 + 192 / this->step * 2, 178 + 126 / this->step * 2, this->window_image, TRUE);
		this->step--;
	}
	return false;
}

bool Menu::updateMain() {
	DrawGraph(80, 100 * this->main_select, this->pointer_image, TRUE);
	Player * temp;
	for (int i = 0; i < this->pc->getNumMember(); i++) {
		temp = this->pc->getMember(i);
		temp->getName(400, 100 + 100 * i, GetColor(0, 0, 0));
		DrawFormatString(600, 100 + 100 * i, GetColor(0, 0, 0), "%d/%d", temp->getHp(), temp->getHpMax());
	}
	DrawFormatString(400, 500, GetColor(0, 0, 0), "所持金 : %d ギル", pc->getNumCoin());
	DrawFormatString(400, 550, GetColor(0, 0, 0), "魔石　 : %d 個", pc->getNumMagicStone());
	if (Button(KEY_INPUT_M) == 1 || Button(KEY_INPUT_B) == 1) {
		this->mode = 5;
	}
	else if (Button(KEY_INPUT_UP) == 1) {
		if (this->main_select - 1 > 0) {
			this->main_select--;
		}
	}
	else if (Button(KEY_INPUT_DOWN) == 1) {
		if (this->main_select + 1 < 5) {
			this->main_select++;
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		this->mode = this->main_select;
	}
	return false;
}

bool Menu::updateItem() {
	int end;
	if (this->pc->getNumItem() == 0) {
		DrawFormatString(350, 100, GetColor(0, 0, 0), "アイテムを所持していません");
	}
	else {
		Item* temp;
		if (pc->getNumItem() < 10 || pc->getNumItem() < this->start + 10) {
			end = pc->getNumItem();
		}
		else {
			end = this->start + 10;
		}
		for (int i = this->start; i < end; i++) {
			temp = pc->getItem(i);
			temp->getName(400, 100 + 50 * (i - this->start));

			DrawGraph(350, 100 + 50 * (this->item_select - this->start), this->pointer_image, TRUE);
		}

		if (this->sub_select == -1) {
			if (Button(KEY_INPUT_UP) % 15 == 1) {
				if (this->item_select - 1 >= 0) {
					this->item_select--;
					if (this->item_select < this->start) {
						this->start--;
					}
				}
			}
			else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
				if (this->item_select + 1 < pc->getNumItem()) {
					this->item_select++;
					if (this->item_select > this->start + 9) {
						this->start++;
					}
				}
			}
			else if (Button(KEY_INPUT_SPACE) == 1) {
				this->sub_select = 0;
			}
		}
		else {
			DrawExtendGraph(850, 400, 1050, 700, this->subwindw_image, TRUE);
			DrawFormatString(900, 450, GetColor(0, 0, 0), "使う");
			DrawFormatString(900, 500, GetColor(0, 0, 0), "すてる");
			int limit = 1;
			if (pc->getItem(this->item_select)->getIsEquip() != 0) {
				DrawFormatString(900, 550, GetColor(0, 0, 0), "装備");
				limit ++;
			}
			DrawGraph(860, 450 + 50 * this->sub_select, this->pointer_image, TRUE);
			if (Button(KEY_INPUT_SPACE) == 1) {
				switch (this->sub_select) {
				case 0:
					this->pc->getItem(this->item_select)->effectMap();
					break;
				case 1:
					this->pc->delItem(this->item_select);
					break;
				case 2:
					this->pc->setEquipment(0, this->item_select);
					break;
				}
				this->sub_select = -1;
			}
			else if (Button(KEY_INPUT_B) == 1) {
				this->sub_select = -1;
			}
			else if (Button(KEY_INPUT_UP) == 1) {
				if (this->sub_select - 1 >= 0) {
					this->sub_select--;
				}
			}
			else if (Button(KEY_INPUT_DOWN) == 1) {
				if (this->sub_select + 1 <= limit) {
					this->sub_select++;
				}
			}
		}
	}
	if (Button(KEY_INPUT_B) == 1) {
		this->mode = 0;
		this->item_select = 0;
		this->start = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		this->mode = 5;
		this->item_select = 0;
		this->start = 0;
	}
	return false;
}

bool Menu::updateEquipment() {
	Player* temp;

	if (this->sub_select == -1) {
		for (int i = 0; i < this->pc->getNumMember(); i++) {
			temp = this->pc->getMember(i);
			temp->getName(400, 100 + 100 * i, GetColor(0, 0, 0));
		}
		DrawGraph(350, 100 + 100 * this->magic_select, this->pointer_image, TRUE);
		if (Button(KEY_INPUT_UP) % 15 == 1) {
			if (this->magic_select - 1 >= 0) {
				this->magic_select--;
			}
		}
		else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if (this->magic_select + 1 < this->pc->getNumMember()) {
				this->magic_select++;
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			this->sub_select = 0;
		}
	}
	else {
		temp = pc->getMember(this->equipment_select);
		DrawFormatString(400, 150, GetColor(0, 0, 0), "武器  : ");
		temp->getWeapon()->getName(600, 150);
		DrawFormatString(400, 200, GetColor(0, 0, 0), "頭装備: ");
		temp->getArmor(5)->getName(600, 200);
		DrawFormatString(400, 250, GetColor(0, 0, 0), "腕装備: ");
		temp->getArmor(4)->getName(600, 250);
		DrawFormatString(400, 300, GetColor(0, 0, 0), "胴装備: ");
		temp->getArmor(3)->getName(600, 300);
		DrawFormatString(400, 350, GetColor(0, 0, 0), "  盾  : ");
		temp->getArmor(2)->getName(600, 350);
	}
	if (Button(KEY_INPUT_B) == 1) {
		this->mode = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		this->mode = 5;
	}
	return false;
}

bool Menu::updateMagic() {
	Player* temp;
	if (this->sub_select == -1) {
		for (int i = 0; i < this->pc->getNumMember(); i++) {
			temp = this->pc->getMember(i);
			temp->getName(400, 100 + 100 * i, GetColor(0, 0, 0));
		}
		DrawGraph(350, 100 + 100 * this->magic_select, this->pointer_image, TRUE);
		if (Button(KEY_INPUT_UP) % 15 == 1) {
			if (this->magic_select - 1 >= 0) {
				this->magic_select--;
			}
		}
		else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if (this->magic_select + 1 < this->pc->getNumMember()) {
				this->magic_select++;
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			this->sub_select = 0;
		}
	}
	else {
		temp = this->pc->getMember(this->magic_select);
		vector <Magic*> magic = temp->getMagics();
		for (int i = 0; i < magic.size(); i++) {
			magic[i]->getName(400, 100 + 50 * i);
		}
		DrawGraph(350, 100 + 50 * this->sub_select, this->pointer_image, TRUE);
		if (Button(KEY_INPUT_UP) % 15 == 1) {
			if (this->sub_select - 1 >= 0) {
				this->sub_select--;
			}
		}
		else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if (this->sub_select + 1 < magic.size()) {
				this->sub_select++;
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			if (magic[this->sub_select]->getIsMap()) {
				magic[this->sub_select]->effectMap();
			}
			else {
				DrawFormatString(300, 550, GetColor(0, 0, 0), "これは使えません。");
			}
		}
	}
	if (Button(KEY_INPUT_B) == 1) {
		this->mode = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		this->mode = 5;
	}
	return false;
}

bool Menu::updateSave() {
	DrawFormatString(400, 150, GetColor(0, 0, 0), "セーブする");
	DrawFormatString(400, 250, GetColor(0, 0, 0), "セーブしない");
	DrawGraph(350, 150 + 100 * this->save_select, this->pointer_image, TRUE);
	if (Button(KEY_INPUT_B) == 1) {
		this->mode = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		this->mode = 5;
	}
	else if (Button(KEY_INPUT_UP) == 1) {
		if (this->save_select == 1) {
			this->save_select = 0;
		}
	}
	else if (Button(KEY_INPUT_DOWN) == 1) {
		if (this->save_select == 0) {
			this->save_select = 1;
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		if (this->save_select == 0) {
			/*
			fstream file;
			file.open("savedata.dat", ios::binary | ios::out);
			file.write((char*)&this->pc, sizeof(this->pc));
			file.close();
			*/
			this->mode = 0;
		}
		else {
			this->save_select = 0;
			this->mode = 0;
		}
	}
	return false;
}

bool Menu::closeWindow() {
	static int temp = 0;
	temp++;
	DrawExtendGraph(242 - 192 / temp, 178 - 126 / temp, 242 + 192 / temp * 2, 178 + 126 / temp * 2, this->window_image, TRUE);
	if (temp == 5) {
		this->mode = 0;
		this->step = temp;
		temp = 0;
		return true;
	}
	return false;
}