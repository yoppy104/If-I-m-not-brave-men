#include "Cleark.h"
#include "DxLib.h"
#include "M_Functions.h"

Cleark::Cleark(string name, int x, int y, vector<ID> item, vector<string> text, std::shared_ptr<PartyControl> pc) : 
	NPC(x, y, name, text, 2),
	items(item),
	itemsInf{},
	start(0),
	num(-1),
	image{0, 0, 0},
	sound{0, 0, 0, 0},
	select_main(0),
	select_sub(0),
	select_sell(-1),
	pc(pc)
{
	for (int i = 0; i < items.size(); i++) {
		itemsInf.push_back(Item(items[i]));
	}

	image.window = LoadGraph("images\\menu.png");
	image.subWindow = LoadGraph("images\\command.png");
	image.pointer = LoadGraph("images\\pointer.png");

	sound.coin = LoadSoundMem("sounds\\SE_coin_2.wav");
	sound.enter = LoadSoundMem("sounds\\SE_enter.wav");
	sound.error = LoadSoundMem("sounds\\SE_error.wav");
	sound.move = LoadSoundMem("sounds\\SE_move.wav");
	sound.cancel = LoadSoundMem("sounds\\SE_cancel.wav");
}

int Cleark::update() {
	DrawExtendGraph(50, 50, 868, 612, image.window, TRUE);
	DrawExtendGraph(1650, 50, 1900, 350, image.subWindow, TRUE);
	DrawFormatString(1700, 100, GetColor(0, 0, 0), "所持金");
	DrawFormatString(1700, 200, GetColor(0, 0, 0), "%dギル", pc->getNumCoin());
	DrawFormatString(100, 100, GetColor(0, 0, 0), "買う");
	DrawFormatString(100, 150, GetColor(0, 0, 0), "売る");
	DrawFormatString(100, 200, GetColor(0, 0, 0), "やめる");
	DrawLine(70, 130 + 50 * select_main, 250, 130 + 50 * select_main, GetColor(0, 0, 0), 5);

	if (num != -1) {
		return buy();
	}
	else if (select_sell != -1) {
		return sell();
	}
	else if (select_sub == -1) {
		if (Button(KEY_INPUT_UP) % 15 == 1) {
			if (select_main - 1 >= 0) {
				PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
				select_main--;
			}
			else{
				PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if (select_main + 1 < 3) {
				PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
				select_main++;
			}
			else{
				PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_B) == 1) {
			PlaySoundMem(sound.cancel, DX_PLAYTYPE_BACK, TRUE);
			return 2;
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
			if (select_main == 0) {
				select_sub = 0;
			}
			else if (select_main == 1) {
				if (pc->getNumItem() != 0) {
					select_sub = 0;
				}
				else {
					return 4;
				}
			}
			else {
				select_main = 0;
				select_sell = -1;
				select_sub = -1;
				return 2;
			}
		}
	}
	else {
		switch (select_main) {
		case 0:
			for (int i = 0; i < items.size(); i++) {
				itemsInf[i].getName(400, 100 + 50 * i);
				DrawFormatString(650, 100 + 50 * i, GetColor(0, 0, 0), "%dギル", itemsInf[i].getPriceBuy());
			}
			DrawLine(390, 130 + 50 * select_sub, 800, 130 + 50 * select_sub, GetColor(0, 0, 0), 5);
			if (Button(KEY_INPUT_UP) % 15 == 1) {
				if (select_sub - 1 >= 0) {
					PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
					select_sub--;
				}
				else{
					PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
				if (select_sub + 1 < items.size()) {
					PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
					select_sub++;
				}
				else{
					PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_SPACE) == 1) {
				PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
				num = 1;
			}
			else if (Button(KEY_INPUT_B) == 1) {
				PlaySoundMem(sound.cancel, DX_PLAYTYPE_BACK, TRUE);
				select_sub = -1;
			}
			break;
		case 1:
			int end;
			if (pc->getNumItem() < 10 || pc->getNumItem() < start + 10) {
				end = pc->getNumItem();
			}
			else {
				end = start + 10;
			}
			for (int i = start; i < end; i++) {
				pc->getItemInfo(i,400, 100 + 50 * i);
			}
			DrawLine(390, 130 + 50 * select_sub, 800, 130 + 50 * select_sub, GetColor(0, 0, 0), 5);
			if (Button(KEY_INPUT_UP) % 15 == 1) {
				if (select_sub - 1 >= 0) {
					PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
					select_sub--;
					if (select_sub < start) {
						start--;
					}
				}
				else{
					PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
				if (select_sub + 1 < pc->getNumItem()) {
					PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
					select_sub++;
					if (select_sub > start + 9) {
						start++;
					}
				}
				else{
					PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (Button(KEY_INPUT_SPACE) == 1) {
				PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
				if (pc->getItemInfo(select_sub)) {
					select_sell = 0;
				}
				else {
					return 5;
				}
			}
			else if (Button(KEY_INPUT_B) == 1) {
				PlaySoundMem(sound.cancel, DX_PLAYTYPE_BACK, TRUE);
				select_sub = -1;
			}
			break;
		}
	}
	return 0;
}

int Cleark::buy() {
	unsigned int col = GetColor(0, 0, 0);
	DrawExtendGraph(800, 500, 1100, 800, image.subWindow, TRUE);
	DrawFormatString(900, 520, col, "何個");
	DrawFormatString(945, 550, col, "↑");
	DrawFormatString(940, 650, col, "%d",num);
	DrawFormatString(945, 750, col, "↓");
	if (Button(KEY_INPUT_UP) % 15 == 1) {
		PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
		num++;
	}
	else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
		if (num - 1 >= 1) {
			PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
			num--;
		}
		else{
			PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_RIGHT) % 15 == 1) {
		PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
		num += 10;
	}
	else if (Button(KEY_INPUT_LEFT) % 15 == 1) {
		if (num - 10 >= 1) {
			PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
			num -= 10;
		}
		else {
			PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
			num = 10;
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
		int price = itemsInf[select_sub].getPriceBuy() * num;
		if (pc->getNumCoin() < price) {
			num = -1;
			return 3;
		}
		else {
			pc->addNumCoin(-1 * price);
			for (int i = 0; i < num; i++) {
				pc->addItem(items[select_sub], num);
			}
			num = -1;
			return 1;
		}
	}
	else if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(sound.cancel, DX_PLAYTYPE_BACK, TRUE);
		num = -1;
	}
	return 0;
}

int Cleark::sell() {
	DrawExtendGraph(800, 500, 1100, 800, image.subWindow, TRUE);
	DrawFormatString(150, 850, GetColor(0, 0, 0), "それなら%dギルで買い取ります。",pc->getItemInfo(select_sub, false));
	DrawFormatString(900, 550, GetColor(0, 0, 0), "売ります");
	DrawFormatString(900, 650, GetColor(0, 0, 0), "はい");
	DrawFormatString(900, 700, GetColor(0, 0, 0), "いいえ");
	DrawLine(890, 680 + 50 * select_sell, 1000, 680 + 50 * select_sell, GetColor(0, 0, 0), 5);
	if (Button(KEY_INPUT_UP) % 15 == 1) {
		if (select_sell - 1 >= 0) {
			PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
			select_sell--;
		}
		else{
			PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
		if (select_sell + 1 < 2) {
			PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
			select_sell++;
		}
		else{
			PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(sound.coin, DX_PLAYTYPE_BACK, TRUE);
		if (select_sell == 0) {
			int price = pc->getItemInfo(select_sub, false);
			pc->delItem(select_sub);
			pc->addNumCoin(price);
			select_sell = -1;
			return 1;
		}
		else {
			select_sell = -1;
		}
	}
	else if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(sound.cancel, DX_PLAYTYPE_BACK, TRUE);
		select_sell = -1;
	}
	return 0;
}

bool Cleark::chat() {
	DrawExtendGraph(100, 800, 1860, 1000, text_box, TRUE);
	getName(150, 810);
	if (step == 1) {
		int test = update();
		if (test == 1) {
			step++;
		}
		else if (test == 2) {
			step = -1;
		}
		else if (test == 3) {
			step = -2;
		}
		else if (test == 4) {
			step = -3;
		}
		else if (test == 5) {
			step = -4;
		}
	}
	else if (step == -1) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), "また来てください。");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
			step = 0;
			return true;
		}
	}
	else if (step == -2) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), "お金が足りませんよ。");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
			step = 0;
			select_main = 0;
			select_sub = -1;
			select_sell = -1;
			num = -1;
			return true;
		}
	}
	else if (step == -3) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), "アイテムを所持していませんよ。");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
			step = 0;
			select_main = 0;
			select_sub = -1;
			select_sell = -1;
			num = -1;
			return true;
		}
	}
	else if (step == -4) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), "それは買い取れませんよ。");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
			step = 0;
			select_main = 0;
			select_sub = -1;
			select_sell = -1;
			num = -1;
			return true;
		}
	}
	else {
  		if (text[step] != "") {
			DrawFormatString(150, 850, GetColor(0, 0, 0), text[step].c_str());
		}
		else {
			step++;
			return false;
		}
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sound.coin, DX_PLAYTYPE_BACK, TRUE);
			if (step == text.size() - 1) {
				step = 0;
				select_main = 0;
				select_sub = -1;
				select_sell = -1;
				num = -1;
				return true;
			}
			step++;
		}
	}
	return false;
}