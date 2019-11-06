#include "Cleark.h"
#include "DxLib.h"
#include "M_Functions.h"

Cleark::Cleark(std::string name, int x, int y, std::vector<ID> item, std::vector<std::string> text, std::shared_ptr<PartyControll> pc) : 
	NPC(x, y, name, text, 2),
	items(item),
	itemsInf{},
	start(0),
	is_buy(false),
	image{0, 0, 0},
	sound{0, 0, 0, 0},
	select_main(0),
	select_sub(-1),
	select_sell(-1),
	is_select_value(true),
	selected_value(0),
	pc(pc)
{
	for (int i = 0; i < items.size(); i++) {
		itemsInf.push_back(Item(items[i]));
	}

	image.window = LoadGraph("images\\System\\menu.png");
	image.subWindow = LoadGraph("images\\System\\command.png");
	image.pointer = LoadGraph("images\\System\\pointer.png");

	sound.coin = LoadSoundMem("sounds\\MapSE\\SE_coin_2.wav");
	sound.enter = LoadSoundMem("sounds\\SystemSE\\SE_enter.wav");
	sound.error = LoadSoundMem("sounds\\SystemSE\\SE_error.wav");
	sound.move = LoadSoundMem("sounds\\SystemSE\\SE_move.wav");
	sound.cancel = LoadSoundMem("sounds\\SystemSE\\SE_cancel.wav");
}

//���t���[���ω�������e�����������B
//�ԋp�l�͎��̏�Ԃ�\��Int�l
int Cleark::update() {
	DrawExtendGraph(50, 50, 868, 612, image.window, TRUE);
	DrawExtendGraph(1650, 50, 1900, 350, image.subWindow, TRUE);
	DrawFormatString(1700, 100, GetColor(0, 0, 0), "������");
	DrawFormatString(1700, 200, GetColor(0, 0, 0), "%d�M��", pc->getNumCoin());
	DrawFormatString(100, 100, GetColor(0, 0, 0), "����");
	DrawFormatString(100, 150, GetColor(0, 0, 0), "����");
	DrawFormatString(100, 200, GetColor(0, 0, 0), "��߂�");
	DrawLine(70, 130 + 50 * select_main, 250, 130 + 50 * select_main, GetColor(0, 0, 0), 5);

	if (is_buy) {
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
				DrawFormatString(650, 100 + 50 * i, GetColor(0, 0, 0), "%d�M��", itemsInf[i].getPriceBuy());
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
				is_buy = true;
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
				//pc->getItem(i).instance->getName(400, 100 + 50 * i);
				pc->GetItemName(i, 400, 100 + 50 * i);
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
				if (pc->getItem(select_sub).instance->getIsSell()) {
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

//�v���C���[���w������Ƃ�
int Cleark::buy() {
	int max_value_buy = pc->getNumCoin() / itemsInf[select_sub].getPriceBuy();
	if (SelectValue(max_value_buy)) {
		PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
		int price = itemsInf[select_sub].getPriceBuy() * selected_value;
		if (pc->getNumCoin() < price) {
			selected_value = 0;
			is_buy = false;
			return 3;
		}
		else {
			pc->addNumCoin(-1 * price);
			pc->addItem(items[select_sub], selected_value);

			selected_value = 0;
			is_buy = false;
			return 1;
		}
	}
	/*
	unsigned int col = GetColor(0, 0, 0);
	DrawExtendGraph(800, 500, 1100, 800, image.subWindow, TRUE);
	DrawFormatString(900, 520, col, "����");
	DrawFormatString(945, 550, col, "��");
	DrawFormatString(940, 650, col, "%d",num);
	DrawFormatString(945, 750, col, "��");
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
	else */
	if (Button(KEY_INPUT_B) == 1) {
		PlaySoundMem(sound.cancel, DX_PLAYTYPE_BACK, TRUE);
		selected_value = -1;
		is_buy = false;
	}
	return 0;
}

//�v���C���[�����p���鎞
int Cleark::sell() {
	DrawExtendGraph(800, 500, 1100, 800, image.subWindow, TRUE);

	if (is_select_value) {
		DrawFormatString(150, 850, GetColor(0, 0, 0), "������܂����H");
		if (SelectValue(pc->getItem(select_sub).num)) {
			is_select_value = false;
		}
	}
	else {
		DrawFormatString(150, 850, GetColor(0, 0, 0), "����Ȃ�%d�M���Ŕ������܂��B", pc->getItem(select_sub).instance->getPriceSell() * selected_value);
		DrawFormatString(900, 550, GetColor(0, 0, 0), "����܂�");
		DrawFormatString(900, 650, GetColor(0, 0, 0), "�͂�");
		DrawFormatString(900, 700, GetColor(0, 0, 0), "������");
		DrawLine(890, 680 + 50 * select_sell, 1000, 680 + 50 * select_sell, GetColor(0, 0, 0), 5);
		if (Button(KEY_INPUT_UP) % 15 == 1) {
			if (select_sell - 1 >= 0) {
				PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
				select_sell--;
			}
			else {
				PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if (select_sell + 1 < 2) {
				PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);
				select_sell++;
			}
			else {
				PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sound.coin, DX_PLAYTYPE_BACK, TRUE);
			if (select_sell == 0) {
				int price = pc->getItem(select_sub).instance->getPriceSell() * selected_value;
				pc->reduceItem(select_sub, selected_value);
				pc->addNumCoin(price);
				select_sell = -1;
				selected_value = 0;
				is_select_value = true;
				return 1;
			}
			else {
				select_sell = -1;
				selected_value = 0;
				is_select_value = true;
			}
		}
		else if (Button(KEY_INPUT_B) == 1) {
			PlaySoundMem(sound.cancel, DX_PLAYTYPE_BACK, TRUE);
			select_sell = -1;
			selected_value = 0;
			is_select_value = true;
		}
	}
	return 0;
}

//�I�[�o�[���C�h���Ďg�p
bool Cleark::chat() {
	DrawExtendGraph(100, 800, 1860, 1000, text_box, TRUE);
	getName(150, 810);
	//Step�Ƃ����l�ŏ�Ԃ��Ǘ����Ă���B
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
	else if (step == -1) {//�I��
		DrawFormatString(150, 850, GetColor(0, 0, 0), "�܂����Ă��������B");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
			step = 0;
			return true;
		}
	}
	else if (step == -2) {//���z�s��
		DrawFormatString(150, 850, GetColor(0, 0, 0), "����������܂����B");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
			step = 0;
			select_main = 0;
			select_sub = -1;
			select_sell = -1;
			return true;
		}
	}
	else if (step == -3) {//�A�C�e����������0�̎��ɔ��p��I��
		DrawFormatString(150, 850, GetColor(0, 0, 0), "�A�C�e�����������Ă��܂����B");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
			step = 0;
			select_main = 0;
			select_sub = -1;
			select_sell = -1;
			return true;
		}
	}
	else if (step == -4) {//���p�s�A�C�e���𔄋p���悤�Ƃ����Ƃ�
		DrawFormatString(150, 850, GetColor(0, 0, 0), "����͔������܂����B");
		if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sound.enter, DX_PLAYTYPE_BACK, TRUE);
			step = 0;
			select_main = 0;
			select_sub = -1;
			select_sell = -1;
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
				return true;
			}
			step++;
		}
	}
	return false;
}


bool Cleark::SelectValue(int max_value) {
	DrawExtendGraph(800, 500, 1000, 700, image.subWindow, TRUE);
	DrawFormatString(887, 537, GetColor(0, 0, 0), "��");
	DrawFormatString(837, 587, GetColor(0, 0, 0), "�� %d ��", selected_value);
	DrawFormatString(887, 637, GetColor(0, 0, 0), "��");

	if (Button(KEY_INPUT_UP) % 15 == 1) {
		PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);

		selected_value++;
		if (selected_value > max_value) {
			PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);

			selected_value = max_value;
		}
	}
	else if (Button(KEY_INPUT_DOWN) % 15 == 1) {
		PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);

		selected_value--;
		if (selected_value < 0) {
			PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);

			selected_value = 0;
		}
	}
	else if (Button(KEY_INPUT_LEFT) % 15 == 1) {
		PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);

		selected_value -= 10;
		if (selected_value < 0) {
			PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);

			selected_value = 0;
		}
	}
	else if (Button(KEY_INPUT_RIGHT) % 15 == 1) {
		PlaySoundMem(sound.move, DX_PLAYTYPE_BACK, TRUE);

		selected_value += 10;
		if (selected_value > max_value) {
			PlaySoundMem(sound.error, DX_PLAYTYPE_BACK, TRUE);
			selected_value = max_value;
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1 || Button(KEY_INPUT_B) == 1) {
		return true;
	}

	return false;
}