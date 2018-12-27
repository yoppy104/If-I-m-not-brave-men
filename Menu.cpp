#include "M_Functions.h"
#include "Menu.h"
#include "DxLib.h"

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
	this->start = 0;
}

Menu::Menu(PartyControl p) {
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
	this->start = 0;
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
	for (int i = 0; i < this->pc.getNumMember(); i++) {
		temp = this->pc.getMember(i);
		temp->getName(400, 100 + 100 * i, GetColor(0, 0, 0));
		DrawFormatString(600, 100 + 100 * i, GetColor(0, 0, 0), "%d/%d", temp->getHp(), temp->getHpMax());
	}
	DrawFormatString(400, 500, GetColor(0, 0, 0), "所持金 : %d ギル", pc.getNumCoin());
	DrawFormatString(400, 550, GetColor(0, 0, 0), "魔石　 : %d 個", pc.getNumMagicStone());
	if (Button(KEY_INPUT_M) == 1) {
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
		this->main_select = 1;
	}
	return false;
}

bool Menu::updateItem() {
	int end;
	if (this->pc.getNumItem() == 0) {
		DrawFormatString(350, 100, GetColor(0, 0, 0), "アイテムを所持していません");
	}
	else {
		Item temp;
		if (pc.getNumItem() < 10 || pc.getNumItem() < this->start + 10) {
			end = pc.getNumItem();
		}
		else {
			end = this->start + 10;
		}
		for (int i = this->start; i < end; i++) {
			temp = pc.getItem(i);
			temp.getName(400, 100 + 50 * (i - this->start));

			DrawGraph(350, 100 + 50 * (this->item_select - this->start), this->pointer_image, TRUE);
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
	else if (Button(KEY_INPUT_UP)%20 == 1) {
		if (this->item_select - 1 >= 0) {
			this->item_select--;
			if (this->item_select < this->start) {
				this->start--;
			}
		}
	}
	else if (Button(KEY_INPUT_DOWN)%20 == 1) {
		if (this->item_select + 1 < pc.getNumItem()) {
			this->item_select++;
			if (this->item_select > this->start + 9) {
				this->start++;
			}
		}
	}
	return false;
}

bool Menu::updateEquipment() {
	DrawFormatString(500, 300, GetColor(0, 0, 0), "装備");
	if (Button(KEY_INPUT_B) == 1) {
		this->mode = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		this->mode = 5;
	}
	return false;
}

bool Menu::updateMagic() {
	DrawFormatString(500, 300, GetColor(0, 0, 0), "魔術");
	if (Button(KEY_INPUT_B) == 1) {
		this->mode = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		this->mode = 5;
	}
	return false;
}

bool Menu::updateSave() {
	DrawFormatString(500, 300, GetColor(0, 0, 0), "セーブ");
	if (Button(KEY_INPUT_B) == 1) {
		this->mode = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		this->mode = 5;
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