#include "M_Functions.h"
#include "Menu.h"
#include "DxLib.h"

Menu::Menu() {
	this->mode = 0;
	this->step = 5;
	this->window_image = LoadGraph("menu.png");
}

bool Menu::Update() {
	if (this->step <= 0) {
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
		// ƒƒjƒ…[‰æ–Ê‚ÌŠJ•Âˆ—
		//w 242 h 178
		DrawExtendGraph(242 - 192 / this->step, 178 - 126 / this->step, 242 + 192 / this->step * 2, 178 + 126 / this->step * 2, this->window_image, TRUE);
		this->step--;
	}
	return false;
}

bool Menu::updateMain() {
	DrawExtendGraph(50, 50, 868, 612, this->window_image, TRUE);
	if (Button(KEY_INPUT_M) == 1) {
		this->mode = 5;
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