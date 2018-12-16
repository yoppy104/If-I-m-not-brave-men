#include "UseMagic.h"
#include "DxLib.h"
#include <cmath>
#include "FireBall.h"
#include "Heal.h"

typedef unsigned long long stagedata;

void searchMagic(int id, Magic* mag) {
	if (id == 1) {
		mag = &FireBall();
	}
}

int searchID(char name[]) {
	if (name == "FireBall") {
		return 1;
	}
}

void showMagic(Player* user, int page) {
	int window_image = LoadGraph("window.png");
	int POSITION_X = 500;
	int POSITION_Y = 200;
	int usable = user->getMagics();

	int start = 16 * (page - 1);

	int test = 1 * pow(2, start);
	DrawGraph(500, 100, window_image, TRUE);

	for (int i = 0; i < 16; i++) {
		if (usable & test) {
			int x, y;
			x = (i < 8) ? POSITION_X + 50 : POSITION_X + 300;
			y = POSITION_Y + 50 * (i % 8);
			if (i == 0) {
				FireBall().getName(x, y);
				DrawFormatString(x + 300, y, GetColor(0, 0, 0), "cost : %d", FireBall().getCost());
			}
			if (i == 1) {
				Heal().getName(x, y);
				DrawFormatString(x + 300, y, GetColor(0, 0, 0), "cost : %d", Heal().getCost());
			}
		}
		test *= 2;
	}
}

bool useMagic(int id, int scene, stagedata stage, Player** players, int user, int size_players, Enemy** enemy, int size_enemy) {
	if (id == 0) {
		if (scene == 0) {
			if (FireBall().effectBattle(stage, players, user, size_players, enemy, size_enemy)) {
				return true;
			}
		}
	}
	else if (id == 1) {
		if (scene == 0) {
			if (Heal().effectBattle(stage, players, user, size_players, enemy, size_enemy)) {
				return true;
			}
		}
	}
	return false;
}