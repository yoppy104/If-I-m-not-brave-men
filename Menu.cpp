#include "M_Functions.h"
#include "Menu.h"
#include "DxLib.h"

Menu::Menu() {
	this->mode = 0;
	this->step = 5;
	this->main_select = 1;
	this->window_image = LoadGraph("menu.png");
	this->pointer_image = LoadGraph("pointer.png");
}

bool Menu::Update() {
	if (this->step <= 0) {
		DrawExtendGraph(50, 50, 868, 612, this->window_image, TRUE);
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
	DrawFormatString(125, 100, GetColor(0, 0, 0), "アイテム");
	DrawFormatString(125, 200, GetColor(0, 0, 0), "装備");
	DrawFormatString(125, 300, GetColor(0, 0, 0), "魔術");
	DrawFormatString(125, 400, GetColor(0, 0, 0), "セーブ");
	DrawGraph(80, 100 * this->main_select, this->pointer_image, TRUE);
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
	return false;
}

bool Menu::updateItem() {

	return false;
}

bool Menu::updateEquipment() {

	return false;
}

bool Menu::updateMagic() {

	return false;
}

bool Menu::updateSave() {

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