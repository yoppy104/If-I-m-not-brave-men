#include "Character.h"
#include "Enemy.h"
#include "Character.h"
#include "Player.h"
#include "DxLib.h"
#include "draw.h"
#include "Mathematic.h"
#include <cstdlib>
#include <time.h>
#include <math.h>

using namespace std;

Enemy::Enemy(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, int image) :Character(name, x, y, hp, attack, diffence, magic_power, dex, image){ // ‰Šú‰»
	
}

bool Enemy::move(int dx, int dy, Player** p, int size_p, Enemy** e, int size_e, stagedata stage) { // “G‚ÌˆÚ“®
	stagedata test = 1; //ˆÚ“®Œã‚ÌˆÊ’uÀ•W
	int test_x = dx + this->getX();
	int test_y = dy + this->getY();
	if ((test_x >= 496 && test_x <= 1296) && (test_y >= 136 && test_y <= 936)) {
		test *= pow(2, round((1296 - test_x) / 160));
		test *= pow(2, 6 * round(((936 - test_y) / 160)));
	}
	else {
		test = 0;
	}

	bool is_p, is_e;
	is_p = false;
	is_e = false;

	for (int i = 0; i < size_p; i++) {
		if (test_x == p[i]->getX() && test_y == p[i]->getY()) {
			is_p = true;
		}
	}

	for (int i = 0; i < size_e; i++) {
		if (test_x == e[i]->getX() && test_y == e[i]->getY()) {
			is_e = true;
		}
	}

	if (is_e || is_p) {
		test = 0;
	}

	if (test & stage) {
		this->setX(test_x);
		this->setY(test_y);
		ClearDrawScreen();
		redraw_battle(stage, e, size_e, p, size_p);
		WaitTimer(300);
		return true;
	}
	else return false;
}

void Enemy::battle(int x, int y, Player** players, int size_players) {
	for (int i = 0; i < size_players; i++) {
		if (this->getX() + x == players[i]->getX() && this->getY() + y == players[i]->getY()) {
			int d = damage(this->getAttack(), players[i]->getDiffence(), 1);
			players[i]->plusHp(d);
			DrawFormatString(players[i]->getX() + 64, players[i]->getY() - 20, GetColor(255, 0, 0), "%d", d);
			WaitTimer(200);
		}
	}
}