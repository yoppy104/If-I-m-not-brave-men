#include "M_Functions.h"
#include "Menu.h"
#include "DxLib.h"
#include <fstream>
#include "Magic.h"
#include "Items.h"

using namespace std;

Menu::Menu(const shared_ptr<PartyControl> p) :
	mode(MAIN),
	step(5),
	mainSelect(1),
	itemSelect(0),
	equipmentSelect(0),
	magicSelect(0),
	saveSelect(0),
	subSelect(-1),
	start(0),
	pc(p),
	images{},
	sounds{}
{
	this->images.window = LoadGraph("menu.png");
	this->images.pointer = LoadGraph("pointer.png");
	this->images.subwindow = LoadGraph("command.png");

	this->sounds.enter = LoadSoundMem("SE_enter.wav");
	this->sounds.error = LoadSoundMem("SE_error.wav");
	this->sounds.move = LoadSoundMem("SE_move.wav");
	this->sounds.cancel = LoadSoundMem("SE_cancel.wav");

}

bool Menu::Update() {
	if (this->step <= 0) {
		DrawExtendGraph(50, 50, 868, 612, this->images.window, TRUE);
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
		DrawExtendGraph(242 - 192 / this->step, 178 - 126 / this->step, 242 + 192 / this->step * 2, 178 + 126 / this->step * 2, this->images.window, TRUE);
		this->step--;
	}
	return false;
}

bool Menu::updateMain() {
	DrawLine(120, 50 + 100 * this->mainSelect, 270, 50 + 100 * this->mainSelect, GetColor(0, 0, 0), 5);
	shared_ptr<Player> temp;
	for (int i = 0; i < this->pc->getNumMember(); i++) {
		temp = this->pc->getMember(i);
		temp->getName(400, 100 + 100 * i, GetColor(0, 0, 0));
		DrawFormatString(600, 100 + 100 * i, GetColor(0, 0, 0), "Lv:%d", temp->GetLV());
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
		PlaySoundMem(this->sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = CLOSE;
	}
	else if (Button(KEY_INPUT_UP) == 1) {
		if (this->mainSelect - 1 > 0) {
			PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
			this->mainSelect--;
		}
		else{
			PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_DOWN) == 1) {
		if (this->mainSelect + 1 < 4) {
			PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
			this->mainSelect++;
		}
		else{
			PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(this->sounds.enter, DX_PLAYTYPE_BACK, TRUE);
		switch (mainSelect) {
		case 0:
			mode = MAIN;
			break;
		case 1:
			mode = ITEM;
			break;
		case 2:
			mode = EQUIPMENT;
			break;
		case 3:
			mode = MAGIC;
			break;
		case 4:
			mode = SAVE;
			break;
		case 5:
			mode = CLOSE;
			break;
		default:
			break;
		}
	}
	return false;
}

bool Menu::updateItem() {
	int end;
	if (this->pc->getNumItem() == 0) {
		DrawFormatString(350, 100, GetColor(0, 0, 0), "アイテムを所持していません");
	}
	else {
		shared_ptr<Item> temp;
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
		DrawLine(350, 120 + 50 * this->itemSelect, 800, 120 + 50 * this->itemSelect, GetColor(0, 0, 0), 5);

		if (this->subSelect == -1) {
			if (Button(KEY_INPUT_UP) % 15 == 1) {
				if (this->itemSelect - 1 >= 0) {
					PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
					this->itemSelect--;
					if (this->itemSelect < this->start) {
						this->start--;
					}
				}
				else {
					PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
				if (this->itemSelect + 1 < pc->getNumItem()) {
					PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
					this->itemSelect++;
					if (this->itemSelect > this->start + 9) {
						this->start++;
					}
				}
				else {
					PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_SPACE) == 1) {
				PlaySoundMem(this->sounds.enter, DX_PLAYTYPE_BACK, TRUE);
				this->subSelect = 0;
			}
		}
		else {
			DrawExtendGraph(850, 400, 1050, 700, this->images.subwindow, TRUE);
			DrawFormatString(900, 450, GetColor(0, 0, 0), "使う");
			DrawFormatString(900, 500, GetColor(0, 0, 0), "すてる");
			int limit = 1;
			if (pc->getItem(this->itemSelect)->getIsEquip() != 0) {
				DrawFormatString(900, 550, GetColor(0, 0, 0), "装備");
				limit ++;
				switch (pc->getItem(this->itemSelect)->getIsEquip()) {
				case 1:
					DrawFormatString(900, 650, GetColor(0, 0, 0), "%d→%d", pc->getMember(0)->getWeapon()->getPoint(), pc->getItem(this->itemSelect)->getPoint());
					break;
				default:
					DrawFormatString(900, 650, GetColor(0, 0, 0), "%d→%d", pc->getMember(0)->getArmor(pc->getItem(this->itemSelect)->getIsEquip())->getPoint(), pc->getItem(this->itemSelect)->getPoint());
					break;
				}
			}
			DrawLine(900, 490 + 50 * this->subSelect, 1000, 490 + 50 * this->subSelect, GetColor(0, 0, 0), 5);
			if (Button(KEY_INPUT_SPACE) == 1) {
				PlaySoundMem(this->sounds.enter, DX_PLAYTYPE_BACK, TRUE);
				switch (this->subSelect) {
				case 0:
					this->pc->getItem(this->itemSelect)->effectMap();
					break;
				case 1:
					if (this->pc->getItem(this->itemSelect)->getIsSell()) {
						this->pc->delItem(this->itemSelect);
					}
					break;
				case 2:
					this->pc->setEquipment(0, this->itemSelect);
					break;
				}
				this->subSelect = -1;
			}
			else if (Button(KEY_INPUT_B) == 1) {
				PlaySoundMem(this->sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
				this->subSelect = -1;
				return false;
			}
			else if (Button(KEY_INPUT_UP) == 1) {
				if (this->subSelect - 1 >= 0) {
					PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
					this->subSelect--;
				}
				else{
					PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_DOWN) == 1) {
				if (this->subSelect + 1 <= limit) {
					PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
					this->subSelect++;
				}
				else {
					PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
		}
	}
	if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(this->sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = MAIN;
		this->itemSelect = 0;
		this->start = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		PlaySoundMem(this->sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = CLOSE;
		this->itemSelect = 0;
		this->start = 0;
	}
	return false;
}

bool Menu::updateEquipment() {
	shared_ptr<Player> temp;
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
	DrawLine(400, 140 + 50 * this->equipmentSelect, 800, 140 + 50 * this->equipmentSelect, GetColor(0, 0, 0), 5);
	if (this->subSelect == -1) {
		if (Button(KEY_INPUT_UP)%15 == 1) {
			if (this->equipmentSelect - 1 >= 0) {
				PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
				this->equipmentSelect--;
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN)%15 == 1) {
			if (this->equipmentSelect + 1 < 5) {
				PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
				this->equipmentSelect++;
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			this->subSelect = 0;
		}
	}
	else {
		DrawExtendGraph(850, 400, 1120, 700, this->images.subwindow, TRUE);
		DrawFormatString(900, 500, GetColor(0, 0, 0), "はずす");
		DrawFormatString(900, 600, GetColor(0, 0, 0), "はずさない");
		DrawLine(890, 540 + 100 * this->subSelect, 1080, 540 + 100 * this->subSelect, GetColor(0, 0, 0), 5);

		if (Button(KEY_INPUT_B) == 1) {
			PlaySoundMem(this->sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
			this->subSelect = -1;
			return false;
		}
		else if (Button(KEY_INPUT_UP) == 1) {
			if (this->subSelect == 1) {
				PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
				this->subSelect = 0;
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) == 1) {
			if (this->subSelect == 0) {
				PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
				this->subSelect = 1;
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			if (this->subSelect == 0) {
				bool check;
				if (this->equipmentSelect + 1 == 1) {
					check = this->pc->getMember(0)->getWeapon()->getId() != NOTEQUIPMENT;
				}
				else {
					check = this->pc->getMember(0)->getArmor(this->equipmentSelect + 1)->getId() != NOTEQUIPMENT;
				}
				if (check) {
					this->pc->replaceEquipment(0, this->equipmentSelect + 1);
				}
				this->subSelect = -1;
				this->equipmentSelect = 0;
			}
			else {
				this->subSelect = -1;
			}
		}
	}
	if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(this->sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = MAIN;
		this->subSelect = -1;
		this->equipmentSelect = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		PlaySoundMem(this->sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = CLOSE;
	}
	return false;
}

bool Menu::updateMagic() {
	shared_ptr<Player> temp = this->pc->getMember(0);
	vector <shared_ptr<Magic>> magic = temp->getMagics();
	for (int i = 0; i < magic.size(); i++) {
		if (!magic[i]->getIsMap()) {
			magic.erase(magic.begin() + i);
			i--;
		}
	}
	int end;
	if (magic.size() < 10 || magic.size() < this->start + 10) {
		end = magic.size();
	}
	else {
		end = this->start + 10;
	}

	for (int i = this->start; i < end; i++) {
		magic[i]->getName(400, 100 + 50 * i);
	}
	DrawLine(390, 140 + 50 * this->magicSelect, 800, 140 + 50 * this->magicSelect, GetColor(0, 0, 0), 5);
	if (this->subSelect == -1) {
		if (Button(KEY_INPUT_UP) % 15 == 1) {
			if (this->magicSelect - 1 >= 0) {
				PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
				this->magicSelect--;
				if (this->itemSelect < this->start) {
					this->start--;
				}
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if (this->magicSelect + 1 < magic.size()) {
				PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
				this->magicSelect++;
				if (this->itemSelect > this->start + 9) {
					this->start++;
				}
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			this->subSelect = 0;
		}
	}
	else if (this->subSelect == 100) {
		if (magic[this->magicSelect]->effectMap(pc)) {
			pc->getMember(0)->plusMp(-1 * magic[this->magicSelect]->getCost());
			this->subSelect = -1;
		}
	}
	else if (this->subSelect == 99) {
		DrawFormatString(400, 700, GetColor(0, 0, 0), "魔力がたりません");
		if (Button(KEY_INPUT_SPACE) == 1) {

		}
	}
	else {
		DrawExtendGraph(850, 400, 1120, 700, this->images.subwindow, TRUE);
		DrawFormatString(900, 500, GetColor(0, 0, 0), "つかう");
		DrawFormatString(900, 600, GetColor(0, 0, 0), "つかわない");
		DrawLine(890, 540 + 100 * this->subSelect, 1080, 540 + 100 * this->subSelect, GetColor(0, 0, 0), 5);
		if (Button(KEY_INPUT_B) == 1) {
			PlaySoundMem(this->sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
			this->subSelect = -1;
			return false;
		}
		else if (Button(KEY_INPUT_UP) == 1) {
			if (this->subSelect == 1) {
				PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
				this->subSelect = 0;
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) == 1) {
			if (this->subSelect == 0) {
				PlaySoundMem(this->sounds.move, DX_PLAYTYPE_BACK, TRUE);
				this->subSelect = 1;
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			if (this->subSelect == 0) {
				if (pc->getMember(0)->getMp() >= magic[this->magicSelect]->getCost()) {
					this->subSelect = 100;
				}
				else {
					this->subSelect = 99;
				}
				this->magicSelect = 0;
			}
			else {
				this->subSelect = -1;
			}
		}
	}
	if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(this->sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = MAIN;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		PlaySoundMem(this->sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		this->mode = CLOSE;
	}
	return false;
}

bool Menu::updateSave() {
	DrawFormatString(400, 150, GetColor(0, 0, 0), "セーブする");
	DrawFormatString(400, 250, GetColor(0, 0, 0), "セーブしない");
	DrawGraph(350, 150 + 100 * this->saveSelect, this->images.pointer, TRUE);
	if (Button(KEY_INPUT_B) == 1) {
		this->mode = MAIN;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		this->mode = CLOSE;
	}
	else if (Button(KEY_INPUT_UP) == 1) {
		if (this->saveSelect == 1) {
			this->saveSelect = 0;
		}
	}
	else if (Button(KEY_INPUT_DOWN) == 1) {
		if (this->saveSelect == 0) {
			this->saveSelect = 1;
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		if (this->saveSelect == 0) {
			this->mode = MAIN;
		}
		else {
			this->saveSelect = 0;
			this->mode = MAIN;
		}
	}
	return false;
}

bool Menu::closeWindow() {
	static int temp = 0;
	temp++;
	DrawExtendGraph(242 - 192 / temp, 178 - 126 / temp, 242 + 192 / temp * 2, 178 + 126 / temp * 2, this->images.window, TRUE);
	if (temp == 5) {
		this->mode = MAIN;
		this->mainSelect = 1;
		this->equipmentSelect = 0;
		this->itemSelect = 0;
		this->magicSelect = 0;
		this->subSelect = -1;
		this->step = temp;
		temp = 0;
		return true;
	}
	return false;
}