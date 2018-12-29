#include "M_Functions.h"
#include "Menu.h"
#include "DxLib.h"
#include <fstream>
#include "Magic.h"
#include "Items.h"

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

	this->sound_enter = LoadSoundMem("SE_enter.wav");
	this->sound_error = LoadSoundMem("SE_error.wav");
	this->sound_move = LoadSoundMem("SE_move.wav");
	this->sound_cancel = LoadSoundMem("SE_cancel.wav");

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

	this->sound_enter = LoadSoundMem("SE_enter.wav");
	this->sound_error = LoadSoundMem("SE_error.wav");
	this->sound_move = LoadSoundMem("SE_move.wav");
	this->sound_cancel = LoadSoundMem("SE_cancel.wav");

}

bool Menu::Update() {
	if (this->step <= 0) {
		DrawExtendGraph(50, 50, 868, 612, this->window_image, TRUE);
		DrawFormatString(125, 100, GetColor(0, 0, 0), "アイテム");
		DrawFormatString(125, 200, GetColor(0, 0, 0), "装備");
		DrawFormatString(125, 300, GetColor(0, 0, 0), "魔術");
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
	DrawLine(120, 50 + 100 * this->main_select, 270, 50 + 100 * this->main_select, GetColor(0, 0, 0), 5);
	Player * temp;
	for (int i = 0; i < this->pc->getNumMember(); i++) {
		temp = this->pc->getMember(i);
		temp->getName(400, 100 + 100 * i, GetColor(0, 0, 0));
		DrawFormatString(600, 100 + 100 * i, GetColor(0, 0, 0), "Lv:%d", temp->getLv());
		DrawFormatString(400, 150 + 100 * i, GetColor(0, 0, 0), "HP:%d/%d", temp->getHp(), temp->getHpMax());
		if (temp->getId() == ALLEN) {
			DrawFormatString(600, 150 + 100 * i, GetColor(0, 0, 0), "MP:%d/%d", temp->getMp(), temp->getMpMax());
		}
		else {
			DrawFormatString(600, 150 + 100 * i, GetColor(0, 0, 0), "MP:――");
		}
	}
	DrawFormatString(400, 500, GetColor(0, 0, 0), "所持金 : %d ギル", pc->getNumCoin());
	DrawFormatString(400, 550, GetColor(0, 0, 0), "魔石　 : %d 個", pc->getNumMagicStone());
	if (Button(KEY_INPUT_M) == 1 || Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = 5;
	}
	else if (Button(KEY_INPUT_UP) == 1) {
		if (this->main_select - 1 > 0) {
			PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
			this->main_select--;
		}
		else{
			PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_DOWN) == 1) {
		if (this->main_select + 1 < 4) {
			PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
			this->main_select++;
		}
		else{
			PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
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
			temp->getName(400, 80 + 50 * (i - this->start));

		}
		DrawLine(350, 120 + 50 * this->item_select, 800, 120 + 50 * this->item_select, GetColor(0, 0, 0), 5);

		if (this->sub_select == -1) {
			if (Button(KEY_INPUT_UP) % 15 == 1) {
				if (this->item_select - 1 >= 0) {
					PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
					this->item_select--;
					if (this->item_select < this->start) {
						this->start--;
					}
				}
				else {
					PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
				if (this->item_select + 1 < pc->getNumItem()) {
					PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
					this->item_select++;
					if (this->item_select > this->start + 9) {
						this->start++;
					}
				}
				else {
					PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_SPACE) == 1) {
				PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
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
			DrawLine(900, 490 + 50 * this->sub_select, 1000, 490 + 50 * this->sub_select, GetColor(0, 0, 0), 5);
			if (Button(KEY_INPUT_SPACE) == 1) {
				PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
				switch (this->sub_select) {
				case 0:
					this->pc->getItem(this->item_select)->effectMap();
					break;
				case 1:
					if (this->pc->getItem(this->item_select)->getIsSell()) {
						this->pc->delItem(this->item_select);
					}
					break;
				case 2:
					this->pc->setEquipment(0, this->item_select);
					break;
				}
				this->sub_select = -1;
			}
			else if (Button(KEY_INPUT_B) == 1) {
				PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
				this->sub_select = -1;
				return false;
			}
			else if (Button(KEY_INPUT_UP) == 1) {
				if (this->sub_select - 1 >= 0) {
					PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
					this->sub_select--;
				}
				else{
					PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_DOWN) == 1) {
				if (this->sub_select + 1 <= limit) {
					PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
					this->sub_select++;
				}
				else {
					PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
		}
	}
	if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = 0;
		this->item_select = 0;
		this->start = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = 5;
		this->item_select = 0;
		this->start = 0;
	}
	return false;
}

bool Menu::updateEquipment() {
	Player* temp;
	temp = pc->getMember(0);
	DrawFormatString(400, 100, GetColor(0, 0, 0), "武器  : ");
	temp->getWeapon()->getName(600, 100);
	DrawFormatString(400, 150, GetColor(0, 0, 0), "  盾  : ");
	temp->getArmor(2)->getName(600, 150);
	DrawFormatString(400, 200, GetColor(0, 0, 0), "胴装備: ");
	temp->getArmor(3)->getName(600, 200);
	DrawFormatString(400, 250, GetColor(0, 0, 0), "腕装備: ");
	temp->getArmor(4)->getName(600, 250);
	DrawFormatString(400, 300, GetColor(0, 0, 0), "頭装備: ");
	temp->getArmor(5)->getName(600, 300);
	DrawLine(400, 140 + 50 * this->equipment_select, 800, 140 + 50 * this->equipment_select, GetColor(0, 0, 0), 5);
	if (this->sub_select == -1) {
		if (Button(KEY_INPUT_UP)%15 == 1) {
			if (this->equipment_select - 1 >= 0) {
				PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
				this->equipment_select--;
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN)%15 == 1) {
			if (this->equipment_select + 1 < 5) {
				PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
				this->equipment_select++;
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
			this->sub_select = 0;
		}
	}
	else {
		DrawExtendGraph(850, 400, 1120, 700, this->subwindw_image, TRUE);
		DrawFormatString(900, 500, GetColor(0, 0, 0), "はずす");
		DrawFormatString(900, 600, GetColor(0, 0, 0), "はずさない");
		DrawLine(890, 540 + 100 * this->sub_select, 1080, 540 + 100 * this->sub_select, GetColor(0, 0, 0), 5);

		if (Button(KEY_INPUT_B) == 1) {
			PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
			this->sub_select = -1;
			return false;
		}
		else if (Button(KEY_INPUT_UP) == 1) {
			if (this->sub_select == 1) {
				PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
				this->sub_select = 0;
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) == 1) {
			if (this->sub_select == 0) {
				PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
				this->sub_select = 1;
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
			if (this->sub_select == 0) {
				bool check;
				if (this->equipment_select + 1 == 1) {
					check = this->pc->getMember(0)->getWeapon()->getId() != NOTEQUIPMENT;
				}
				else {
					check = this->pc->getMember(0)->getArmor(this->equipment_select + 1)->getId() != NOTEQUIPMENT;
				}
				if (check) {
					this->pc->replaceEquipment(0, this->equipment_select + 1);
				}
				this->sub_select = -1;
				this->equipment_select = 0;
			}
			else {
				this->sub_select = -1;
			}
		}
	}
	if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = 0;
		this->sub_select = -1;
		this->equipment_select = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
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
		if (Button(KEY_INPUT_UP) % 15 == 1) {
			if (this->magic_select - 1 >= 0) {
				PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
				this->magic_select--;
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if (this->magic_select + 1 < this->pc->getNumMember()) {
				PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
				this->magic_select++;
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
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
				PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
				this->sub_select--;
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if (this->sub_select + 1 < magic.size()) {
				PlaySoundMem(this->sound_move, DX_PLAYTYPE_BACK, TRUE);
				this->sub_select++;
			}
			else{
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			if (magic[this->sub_select]->getIsMap()) {
				PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
				magic[this->sub_select]->effectMap();
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
				DrawFormatString(300, 550, GetColor(0, 0, 0), "これは使えません。");
			}
		}
	}
	if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		PlaySoundMem(this->sound_cancel, DX_PLAYTYPE_BACK, TRUE);
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
			this->pc->getMember(0)->save();
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