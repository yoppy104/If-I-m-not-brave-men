#include "Magic.h"
#include "FireBall.h"
#include "draw.h"

typedef unsigned long long stagedata;

FireBall::FireBall() :Magic(1, "ファイアボール", 5, false) {
	this->damage = 10;
	this->type = 1;
	this->attack_area = 11;
	this->attackable = 2;
}

void FireBall::effectpoint(int point, Player** players, int size_players, Enemy** enemy, int size_enemy) {
	int point_x = point % 10; //カーソルのx座標
	int point_y = point / 10; //カーソルのy座標
	int i;
	bool is_end = false;
	int image = LoadGraph("damage.png");
	for (i = 0; i < size_enemy; i++) {
		if (496 + 160 * point_x == enemy[i]->getX() && 136 + 160 * point_y == enemy[i]->getY()) {
			is_end = true;
			enemy[i]->plusHp(-1 * this->damage); //体力を減少
			DrawGraph(enemy[i]->getX() + 32, enemy[i]->getY() - 45, image, TRUE);
			DrawFormatString(enemy[i]->getX() + 50, enemy[i]->getY() - 32, GetColor(150, 0, 40), "%d", this->damage); //ダメージを表記
			WaitTimer(150);
			break;
		}
	}
	if (!is_end) {
		for (i = 0; i < size_players; i++) {
			if (496 + 160 * point_x == players[i]->getX() && 136 + 160 * point_y == players[i]->getY()) {
				is_end = true;
				players[i]->plusHp(-1 * this->damage); //体力を減少
				DrawGraph(players[i]->getX() + 32, players[i]->getY() - 45, image, TRUE);
				DrawFormatString(players[i]->getX() + 50, players[i]->getY() - 32, GetColor(150, 0, 40), "%d", this->damage); //ダメージを表記
				WaitTimer(150);
				break;
			}
		}
	}
}

bool FireBall::effectBattle(stagedata stage, Player** players, int user, int size_players, Enemy** enemy, int size_enemy) {
	redraw_battle(stage, enemy, size_enemy, players, size_players);
	int point = draw_attackable_area(players[user], players, size_players, enemy, size_enemy, this->attackable);
	draw_attack_area(point, players[user], 11);
	int x = (players[user]->getX() - 496) / 160;
	int y = (players[user]->getY() - 136) / 160;
	while (CheckHitKey(KEY_INPUT_SPACE) == 0) {
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			if ((point % 10) + 1 < 6) {
				if ((point % 10) + 1 <= x + this->attackable) {
					point += 1;
					ClearDrawScreen();
					redraw_battle(stage, enemy, size_enemy, players, size_players);
					draw_attackable_area(players[user], players, size_players, enemy, size_enemy, this->attackable);
					draw_attack_area(point, players[user], 11);
				}
			}
			while (CheckHitKey(KEY_INPUT_RIGHT)) {}
		}
		else if (CheckHitKey(KEY_INPUT_LEFT)) {
			if ((point % 10) - 1 >= 0) {
				if ((point % 10) - 1 >= x - this->attackable) {
					point -= 1;
					ClearDrawScreen();
					redraw_battle(stage, enemy, size_enemy, players, size_players);
					draw_attackable_area(players[user], players, size_players, enemy, size_enemy, this->attackable);
					draw_attack_area(point, players[user], 11);
				}
			}
			while (CheckHitKey(KEY_INPUT_LEFT)) {}
		}
		else if (CheckHitKey(KEY_INPUT_UP)) {
			if ((point / 10) - 1 >= 0) {
				if ((point / 10) - 1 >= y - this->attackable) {
					point -= 10;
					ClearDrawScreen();
					redraw_battle(stage, enemy, size_enemy, players, size_players);
					draw_attackable_area(players[user], players, size_players, enemy, size_enemy, this->attackable);
					draw_attack_area(point, players[user], 11);
				}
			}
			while (CheckHitKey(KEY_INPUT_UP)) {}
		}
		else if (CheckHitKey(KEY_INPUT_DOWN)) {
			if ((point / 10) + 1 < 6) {
				if ((point / 10) + 1 <= y + this->attackable) {
					point += 10;
					ClearDrawScreen();
					redraw_battle(stage, enemy, size_enemy, players, size_players);
					draw_attackable_area(players[user], players, size_players, enemy, size_enemy, this->attackable);
					draw_attack_area(point, players[user], 11);
				}
			}
			while (CheckHitKey(KEY_INPUT_DOWN)) {}
		}
		else if (CheckHitKey(KEY_INPUT_B)) {
			return true;
		}
	}
	while (CheckHitKey(KEY_INPUT_SPACE)) {}

	int sound = LoadSoundMem("銃火器・大砲02.mp3");
	int sound_charge = LoadSoundMem("魔法的音06.mp3");
	int image_circle = LoadGraph("magiccircle.png");
	DrawGraph(players[user]->getX(), players[user]->getY(), image_circle, TRUE);
	PlaySoundMem(sound_charge, DX_PLAYTYPE_NORMAL, TRUE);
	for (int i = 0; i < 4; i++) {
		ClearDrawScreen();
		redraw_battle(stage, enemy, size_enemy, players, size_players);
		draw_attack_animation(496 + 160 * (int)(point % 10), 136 + 160 * (int)(point / 10), players[user]->getX(), players[user]->getY(), 4, i);
		WaitTimer(5);
	}
	PlaySoundMem(sound, DX_PLAYTYPE_BACK, TRUE);

	this->effectpoint(point, players, size_players, enemy, size_enemy);



	WaitTimer(500);


	return false;
}

void FireBall::effectMap() {
	DrawFormatString(100, 100, GetColor(0, 0, 0), "test");
}