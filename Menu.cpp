#include "M_Functions.h"
#include "Menu.h"

Menu::Menu() {
	this->mode = 0;
	this->step = 0;
}

bool Menu::Update() {
	if (this->step != 0) {
		switch (this->mode) {
		case 0:
			this->updateMain();
			break;
		case 1:
			this->updateItem();
			break;
		case 2:
			this->updateEquipment();
			break;
		case 3:
			this->updateMagic();
			break;
		case 4:
			this->updateSave();
			break;
		}
	}
	else {
		// ƒƒjƒ…[‰æ–Ê‚ÌŠJ•Âˆ—
		this->step++;
	}
	return false;
}

void Menu::updateMain() {

}

void Menu::updateItem() {

}

void Menu::updateEquipment() {

}

void Menu::updateMagic() {

}

void Menu::updateSave() {

}