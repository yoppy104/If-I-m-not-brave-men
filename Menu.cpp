#include "M_Functions.h"
#include "Menu.h"
#include "DxLib.h"
#include <fstream>
#include "Magic.h"

using namespace std;

Menu::Menu(std::shared_ptr<PartyControl> p) :
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
	images.window = LoadGraph("images\\menu.png");
	images.pointer = LoadGraph("images\\pointer.png");
	images.subwindow = LoadGraph("images\\command.png");

	sounds.enter = LoadSoundMem("sound/SE_enter.wav");
	sounds.error = LoadSoundMem("sound/SE_error.wav");
	sounds.move = LoadSoundMem("sound/SE_move.wav");
	sounds.cancel = LoadSoundMem("sound/SE_cancel.wav");

}

bool Menu::Update() {
	if (step <= 0) {
		DrawExtendGraph(50, 50, 868, 612, images.window, TRUE);
		DrawFormatString(125, 100, GetColor(0, 0, 0), "アイテム");
		DrawFormatString(125, 200, GetColor(0, 0, 0), "装備");
		DrawFormatString(125, 300, GetColor(0, 0, 0), "魔術");
		switch (mode) {
		case 0:
			return updateMain();
			break;
		case 1:
			return updateItem();
			break;
		case 2:
			return updateEquipment();
			break;
		case 3:
			return updateMagic();
			break;
		case 4:
			return updateSave();
			break;
		case 5:
			return closeWindow();
			break;
		}
	}
	else {
		// メニュー画面の開閉処理
		//w 242 h 178
		DrawExtendGraph(242 - 192 / step, 178 - 126 / step, 242 + 192 / step * 2, 178 + 126 / step * 2, images.window, TRUE);
		step--;
	}
	return false;
}

bool Menu::updateMain() {
	DrawLine(120, 50 + 100 * mainSelect, 270, 50 + 100 * mainSelect, GetColor(0, 0, 0), 5);
	std::shared_ptr<Player> temp;
	for (int i = 0; i < pc->getNumMember(); i++) {
		temp = pc->getMember(i);
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
		PlaySoundMem(sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		mode = CLOSE;
	}
	else if (Button(KEY_INPUT_UP) == 1) {
		if (mainSelect - 1 > 0) {
			PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
			mainSelect--;
		}
		else{
			PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_DOWN) == 1) {
		if (mainSelect + 1 < 4) {
			PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
			mainSelect++;
		}
		else{
			PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(sounds.enter, DX_PLAYTYPE_BACK, TRUE);
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
	if (pc->getNumItem() == 0) {
		DrawFormatString(350, 100, GetColor(0, 0, 0), "アイテムを所持していません");
	}
	else {
		std::shared_ptr<Item> temp;
		if (pc->getNumItem() < 10 || pc->getNumItem() < start + 10) {
			end = pc->getNumItem();
		}
		else {
			end = start + 10;
		}
		for (int i = start; i < end; i++) {
			pc->getItemInfo(i, 400, 80 + 50 * (i - start));

		}
		DrawLine(350, 120 + 50 * itemSelect, 800, 120 + 50 * itemSelect, GetColor(0, 0, 0), 5);

		if (subSelect == -1) {
			if (Button(KEY_INPUT_UP) % 15 == 1) {
				if (itemSelect - 1 >= 0) {
					PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
					itemSelect--;
					if (itemSelect < start) {
						start--;
					}
				}
				else {
					PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
				if (itemSelect + 1 < pc->getNumItem()) {
					PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
					itemSelect++;
					if (itemSelect > start + 9) {
						start++;
					}
				}
				else {
					PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_SPACE) == 1) {
				PlaySoundMem(sounds.enter, DX_PLAYTYPE_BACK, TRUE);
				subSelect = 0;
			}
		}
		else {
			DrawExtendGraph(850, 400, 1050, 700, images.subwindow, TRUE);
			DrawFormatString(900, 450, GetColor(0, 0, 0), "使う");
			DrawFormatString(900, 500, GetColor(0, 0, 0), "すてる");
			int limit = 1;
			if (pc->getItemIsEquip(itemSelect) != 0) {
				DrawFormatString(900, 550, GetColor(0, 0, 0), "装備");
				limit ++;
				DrawFormatString(900, 650, GetColor(0, 0, 0), "%d→%d", pc->getMember(0)->getEquipPoint(pc->getItemIsEquip(itemSelect)), pc->getItemPoint(itemSelect));
			}
			DrawLine(900, 490 + 50 * subSelect, 1000, 490 + 50 * subSelect, GetColor(0, 0, 0), 5);
			if (Button(KEY_INPUT_SPACE) == 1) {
				PlaySoundMem(sounds.enter, DX_PLAYTYPE_BACK, TRUE);
				switch (subSelect) {
				case 0:
					pc->useItemMap(itemSelect);
					break;
				case 1:
					if (pc->getItemInfo(itemSelect)) {
						pc->delItem(itemSelect);
					}
					break;
				case 2:
					pc->setEquipment(0, itemSelect);
					break;
				}
				subSelect = -1;
			}
			else if (Button(KEY_INPUT_B) == 1) {
				PlaySoundMem(sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
				subSelect = -1;
				return false;
			}
			else if (Button(KEY_INPUT_UP) == 1) {
				if (subSelect - 1 >= 0) {
					PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
					subSelect--;
				}
				else{
					PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_DOWN) == 1) {
				if (subSelect + 1 <= limit) {
					PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
					subSelect++;
				}
				else {
					PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
		}
	}
	if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		mode = MAIN;
		itemSelect = 0;
		start = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		PlaySoundMem(sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		mode = CLOSE;
		itemSelect = 0;
		start = 0;
	}
	return false;
}

bool Menu::updateEquipment() {
	std::shared_ptr<Player> temp;
	temp = pc->getMember(0);
	DrawFormatString(400, 100, GetColor(0, 0, 0), "武器  : ");
	temp->getEquipName(1, 600, 100);
	DrawFormatString(400, 150, GetColor(0, 0, 0), "  盾  : ");
	temp->getEquipName(2, 600, 150);
	DrawFormatString(400, 200, GetColor(0, 0, 0), "胴装備: ");
	temp->getEquipName(3, 600, 200);
	DrawFormatString(400, 250, GetColor(0, 0, 0), "腕装備: ");
	temp->getEquipName(4, 600, 250);
	DrawFormatString(400, 300, GetColor(0, 0, 0), "頭装備: ");
	temp->getEquipName(5, 600, 300);
	DrawLine(400, 140 + 50 * equipmentSelect, 800, 140 + 50 * equipmentSelect, GetColor(0, 0, 0), 5);
	if (subSelect == -1) {
		if (Button(KEY_INPUT_UP)%15 == 1) {
			if (equipmentSelect - 1 >= 0) {
				PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
				equipmentSelect--;
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN)%15 == 1) {
			if (equipmentSelect + 1 < 5) {
				PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
				equipmentSelect++;
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			subSelect = 0;
		}
	}
	else {
		DrawExtendGraph(850, 400, 1120, 700, images.subwindow, TRUE);
		DrawFormatString(900, 500, GetColor(0, 0, 0), "はずす");
		DrawFormatString(900, 600, GetColor(0, 0, 0), "はずさない");
		DrawLine(890, 540 + 100 * subSelect, 1080, 540 + 100 * subSelect, GetColor(0, 0, 0), 5);

		if (Button(KEY_INPUT_B) == 1) {
			PlaySoundMem(sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
			subSelect = -1;
			return false;
		}
		else if (Button(KEY_INPUT_UP) == 1) {
			if (subSelect == 1) {
				PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
				subSelect = 0;
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) == 1) {
			if (subSelect == 0) {
				PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
				subSelect = 1;
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			if (subSelect == 0) {
				bool check = pc->getMember(0)->hasEquip(equipmentSelect + 1);
				if (check) {
					pc->replaceEquipment(0, equipmentSelect + 1);
				}
				subSelect = -1;
				equipmentSelect = 0;
			}
			else {
				subSelect = -1;
			}
		}
	}
	if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		mode = MAIN;
		subSelect = -1;
		equipmentSelect = 0;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		PlaySoundMem(sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		mode = CLOSE;
	}
	return false;
}

bool Menu::updateMagic() {
	std::shared_ptr<Player> temp = pc->getMember(0);
	int skip = 0;
	int end;
	if (temp->getNumMagicMap() < 10 || temp->getNumMagicMap() < start + 10) {
		end = temp->getNumMagicMap();
	}
	else {
		end = start + 10;
	}

	for (int i = start; i < end; i++) {
		temp->getMagicInfo(i, 400, 100 + 50 * i, true);
	}
	DrawLine(390, 140 + 50 * magicSelect, 800, 140 + 50 * magicSelect, GetColor(0, 0, 0), 5);
	if (subSelect == -1) {
		if (Button(KEY_INPUT_UP) % 15 == 1) {
			if (magicSelect - 1 >= 0) {
				PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
				magicSelect--;
				if (itemSelect < start) {
					start--;
				}
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if (magicSelect + 1 < temp->getNumMagicMap()) {
				PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
				magicSelect++;
				if (itemSelect > start + 9) {
					start++;
				}
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			subSelect = 0;
		}
	}
	else if (subSelect == 100) {
		if (temp->useMagicMap(magicSelect,pc)) {
			subSelect = -1;
		}
	}
	else if (subSelect == 99) {
		DrawFormatString(400, 700, GetColor(0, 0, 0), "魔力がたりません");
		if (Button(KEY_INPUT_SPACE) == 1) {

		}
	}
	else {
		DrawExtendGraph(850, 400, 1120, 700, images.subwindow, TRUE);
		DrawFormatString(900, 500, GetColor(0, 0, 0), "つかう");
		DrawFormatString(900, 600, GetColor(0, 0, 0), "つかわない");
		DrawLine(890, 540 + 100 * subSelect, 1080, 540 + 100 * subSelect, GetColor(0, 0, 0), 5);
		if (Button(KEY_INPUT_B) == 1) {
			PlaySoundMem(sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
			subSelect = -1;
			return false;
		}
		else if (Button(KEY_INPUT_UP) == 1) {
			if (subSelect == 1) {
				PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
				subSelect = 0;
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) == 1) {
			if (subSelect == 0) {
				PlaySoundMem(sounds.move, DX_PLAYTYPE_BACK, TRUE);
				subSelect = 1;
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			if (subSelect == 0) {
				if (temp->useMagicMap(magicSelect, pc) != -1) {
					subSelect = 100;
				}
				else {
					subSelect = 99;
				}
				magicSelect = 0;
			}
			else {
				subSelect = -1;
			}
		}
	}
	if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		mode = MAIN;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		PlaySoundMem(sounds.cancel, DX_PLAYTYPE_BACK, TRUE);
		mode = CLOSE;
	}
	return false;
}

bool Menu::updateSave() {
	DrawFormatString(400, 150, GetColor(0, 0, 0), "セーブする");
	DrawFormatString(400, 250, GetColor(0, 0, 0), "セーブしない");
	DrawGraph(350, 150 + 100 * saveSelect, images.pointer, TRUE);
	if (Button(KEY_INPUT_B) == 1) {
		mode = MAIN;
	}
	else if (Button(KEY_INPUT_M) == 1) {
		mode = CLOSE;
	}
	else if (Button(KEY_INPUT_UP) == 1) {
		if (saveSelect == 1) {
			saveSelect = 0;
		}
	}
	else if (Button(KEY_INPUT_DOWN) == 1) {
		if (saveSelect == 0) {
			saveSelect = 1;
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		if (saveSelect == 0) {
			mode = MAIN;
		}
		else {
			saveSelect = 0;
			mode = MAIN;
		}
	}
	return false;
}

bool Menu::closeWindow() {
	static int temp = 0;
	temp++;
	DrawExtendGraph(242 - 192 / temp, 178 - 126 / temp, 242 + 192 / temp * 2, 178 + 126 / temp * 2, images.window, TRUE);
	if (temp == 5) {
		mode = MAIN;
		mainSelect = 1;
		equipmentSelect = 0;
		itemSelect = 0;
		magicSelect = 0;
		subSelect = -1;
		step = temp;
		temp = 0;
		return true;
	}
	return false;
}