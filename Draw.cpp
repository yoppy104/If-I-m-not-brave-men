#include "draw.h"
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Equipment.h"

typedef uint64_t stagedata;

void battle_stage(stagedata stage) {
	stagedata test = 1 * pow(2, 35);//見る値の範囲を36マスに限定する
	int image_stage = LoadGraph("battlepanel.png"); //通常マス
	int image_stagenot = LoadGraph("not_battlepanel.png"); //通行不能マス
	int up = 136; //左上のy座標
	int left = 496; //左上のx座標
	while (test >= 1) {
		if (stage & test) {
			DrawGraph(left, up, image_stage, TRUE);
		}
		else {
			DrawGraph(left, up, image_stagenot, TRUE);
		}
		test /= 2;
		left += 160;
		if (left > 1296) {
			left = 496;

			up += 160;
		}
	}
	DeleteGraph(image_stage);
	DeleteGraph(image_stagenot);
}

void redraw_battle(stagedata stage, Enemy *_enemy, Player *_player) {
	int background = LoadGraph("bg_natural_sougen.jpg"); // 背景画像

	DrawGraph(0, 0, background, TRUE);
	battle_stage(stage);
	DrawGraph(_enemy->getX(), _enemy->getY(), _enemy->getImage(), TRUE);
	DrawGraph(_player->getX(), _player->getY(), _player->getImage(), TRUE);

	DeleteGraph(background);
}

void draw_command(int sele) { //コマンド描画の関数
	int command = LoadGraph("command.png"); // コマンドパネル
	int point = LoadGraph("pointer.png"); // コマンド選択用のポインタ画像

	DrawRotaGraph(200, 400, 2.0, 0, command, TRUE); //コマンドフレームの描画
	DrawRotaGraph(120, 220 + 200 * sele, 1.5, 0, point, TRUE); // 選択用ポインタの描画
	DrawFormatString(150, 200, GetColor(0, 0, 0), "たたかう");
	DrawFormatString(150, 400, GetColor(0, 0, 0), "いどう");

	DeleteGraph(command);
	DeleteGraph(point);
}

int draw_attackable_area(Player me, Enemy enemy) { // 後に配列に変更
	int player_x = me.getX(); // 対象プレイヤーのx座標
	int player_y = me.getY(); // 対象プレイヤーのy座標
	Equipment arm = me.getEquipment();
	int attackable_image = LoadGraph("attackpanel.png");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	if (arm.getAttackable()  == -1) {
		for (int x = 496; x <= 1296; x += 160) {
			for (int y = 136; y <= 936; y += 160) {
				if (! (x == player_x && y == player_y)) {
					DrawGraph(x, y, attackable_image, TRUE);
					if (player_x == x && player_y == y) {
						DrawGraph(me.getX(), me.getY(), me.getImage(), TRUE);
					}
					if (enemy.getX() == x && enemy.getY() == y) {
						DrawGraph(enemy.getX(), enemy.getY(), enemy.getImage(), TRUE);
					}
				}
			}
		}
	}
	else {
		for (int x = -1 * (arm.getAttackable()); x <= arm.getAttackable(); x++) {
			for (int y = -1 * (arm.getAttackable()); y <= arm.getAttackable(); y++) {
				if ((x != 0 || y != 0) && (player_x + 160 * x >= 496 && player_x + 160*x <= 1296) && (player_y + 160*y >= 136 && player_y +160*y <= 936)) {
					DrawGraph(player_x + 160 * x, player_y + 160 * y, attackable_image, TRUE);
				}
			}
		}
	}

	int result = ((player_x - 496) / 160) + ((player_y - 136) / 160) * 10; // カーソルの初期位置は攻撃キャラ

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DeleteGraph(attackable_image);

	return result;
}

void draw_attack_area(int point) {
	int x = point % 10;
	int y = (point - x) / 10;
	int frame = LoadGraph("battleframe.png");
	DrawGraph(496 + 160 * x, 136 + 160 * y, frame, TRUE);

	DeleteGraph(frame);
}
