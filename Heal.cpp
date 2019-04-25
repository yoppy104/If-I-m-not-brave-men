# include "Heal.h"
#include "DxLib.h"
#include "draw.h"
#include "M_Functions.h"

Heal::Heal() :Magic(2, "ƒq[ƒ‹", 2, true) {
	this->point = 20;
	this->type = 1;
	this->attack_area = 11;
	this->attackable = 2;
}


bool Heal::effectBattle(stagedata stage, Player** players, int user, int size_players, Enemy** enemy, int size_enemy) {
	return false;
}

bool Heal::effectMap(PartyControl* pc) {
	int window = LoadGraph("command.png");
	DrawExtendGraph(800, 300, 1600, 800, window, TRUE);
	DrawFormatString(850, 350, GetColor(0, 0, 0), "‰ñ•œ‚·‚é‘ÎÛ‚ğ‘I‚ñ‚Å‚­‚¾‚³‚¢B");
	int col = 0;
	Player* temp;
	for (int i = 0; i < pc->getNumMember(); i++) {
		temp = pc->getMember(i);
		if ((double)temp->getHp() / (double)temp->getHpMax() > 0.8) {
			col = GetColor(0, 0, 255);
		}
		else {
			col = GetColor(255, 0, 0);
		}
		temp->getName(850, 450 + 50 * i, col);
	}
	int select = 0;
	DrawLine(840, 480 + 50 * select, 1450, 480 + 50 * select, GetColor(0, 0, 0), TRUE);

	int sound_move = LoadSoundMem("SE_move.wav");
	int sound_error = LoadSoundMem("SE_error.wav");
	int sound_heal = LoadSoundMem("SE_heal.wav");

	if (Button(KEY_INPUT_UP) == 1) {
		if (select - 1 >= 0) {
			PlaySoundMem(sound_move, DX_PLAYTYPE_BACK, TRUE);
			select--;
		}
		else{
			PlaySoundMem(sound_error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_DOWN) == 1) {
		if (select + 1 < pc->getNumMember()) {
			PlaySoundMem(sound_move, DX_PLAYTYPE_BACK, TRUE);
			select++;
		}
		else{
			PlaySoundMem(sound_error, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (Button(KEY_INPUT_SPACE) == 1) {
		PlaySoundMem(sound_heal, DX_PLAYTYPE_BACK, TRUE);
		pc->getMember(select)->healHp(this->point);
		return true;
	}
	return false;
}