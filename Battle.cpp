#include "DxLib.h"
#include "Battle.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "Weapon.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "draw.h"
#include "Mathematic.h"

typedef uint8_t datatable;
typedef unsigned long long stagedata;

//本文
void Battle(Player* players, int size_players)
{
	int enemy_image = LoadGraph("enemy.png"); // 敵の画像
	int frame_image = LoadGraph("battleframe->png"); // 攻撃範囲の選択用

	//ステージのデータ値
	stagedata stage = 0b1111111111111111111011111111111111111;

	int battlemap_left = 496; // マップの左の座標
	int battlemap_top = 136; // マップの上の座標

	Enemy enemy_a("スライム", 496 + 160 * 2, 136 + 160 * 0, 5, 2, 100, 2, 4, enemy_image); // スライムの構造体定義
	Enemy enemy_b("スライム", 496 + 160 * 0, 136 + 160 * 0, 5, 2, 100, 2, 4, enemy_image); // スライムの構造体定義
	Enemy enemy_c("スライム", 496 + 160 * 1, 136 + 160 * 0, 5, 2, 100, 2, 4, enemy_image); // スライムの構造体定義
	Enemy enemy[3] = { enemy_a, enemy_b, enemy_c };

	int size_enemy = sizeof(enemy) / sizeof(enemy[0]);

	int select_do; //グループ全体での行動選択
	int select; //個人での行動選択
	bool is_loop = true;
	while (is_loop && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		select_do = 0; //0:行動,　1:逃げる
		ClearDrawScreen();
		redraw_battle(stage, enemy, size_enemy, players, size_players);
		draw_command_do(select_do); //コマンド枠を描画
		while (CheckHitKey(KEY_INPUT_SPACE) == 0) {
			if (CheckHitKey(KEY_INPUT_UP)) {
				if (select_do == 1) {
					select_do--;
					ClearDrawScreen();
					redraw_battle(stage, enemy, size_enemy, players, size_players);
					draw_command_do(select_do);
				}
				while (CheckHitKey(KEY_INPUT_UP)) {}
			}
			else if (CheckHitKey(KEY_INPUT_DOWN)) {
				if (select_do == 0) {
					select_do++;
					ClearDrawScreen();
					redraw_battle(stage, enemy, size_enemy, players, size_players);
					draw_command_do(select_do);
				}
				while (CheckHitKey(KEY_INPUT_DOWN)) {}
			}
		}
		while (CheckHitKey(KEY_INPUT_SPACE)){}

		if (select_do == 0) { //戦闘を行う場合

			//行動決定

			//ここまで


			for (int i = 0; i < 1; i++) {

				int side = 0 / 10; //どっちサイドか
				int person = 0 % 10; //各サイドのどの人か

				if (side == 0) { //味方サイドの行動
					Player *me = &players[person];
					select = 0; // 0:攻撃 1:いどう 2:アイテム 3:防御
					ClearDrawScreen();
					redraw_battle(stage, enemy, size_enemy, players, size_players);
					draw_command(select); //コマンド枠を描画

					// 行動の選択
					while (CheckHitKey(KEY_INPUT_SPACE) == 0 && CheckHitKey(KEY_INPUT_B) == 0) { // spaceを押したら決定
						if (CheckHitKey(KEY_INPUT_DOWN)) { // 下を押したらselectを+1
							if (select == 0) {
								select++;
								ClearDrawScreen();
								redraw_battle(stage, enemy, size_enemy, players, size_players);
								draw_command(select);
							}
							while (CheckHitKey(KEY_INPUT_DOWN)) {}
						}
						else if (CheckHitKey(KEY_INPUT_UP)) { // 上を押したらselectを―1
							if (select == 1) {
								select--;
								ClearDrawScreen();
								redraw_battle(stage, enemy, size_enemy, players, size_players);
								draw_command(select);
							}
							while (CheckHitKey(KEY_INPUT_UP)) {}
						}
					}
					while (CheckHitKey(KEY_INPUT_B)) {
						select = -1;
					}
					while (CheckHitKey(KEY_INPUT_SPACE)) {}

					redraw_battle(stage, enemy, size_enemy, players, size_players);

					if (select == 0) { //通常攻撃
						int point = draw_attackable_area(me, players, size_players, enemy, size_enemy);
						draw_attack_area(point, me);
						while (CheckHitKey(KEY_INPUT_SPACE) == 0) {
							if (CheckHitKey(KEY_INPUT_RIGHT)) {
								if ((point % 10) + 1 < 6) {
									if (me->is_attackable(point + 1)) {
										point += 1;
										ClearDrawScreen();
										redraw_battle(stage, enemy, size_enemy, players, size_players);
										draw_attackable_area(me, players, size_players, enemy, size_enemy);
										draw_attack_area(point, me);
									}
								}
								while (CheckHitKey(KEY_INPUT_RIGHT)) {}
							}
							else if (CheckHitKey(KEY_INPUT_LEFT)) {
								if ((point % 10) - 1 >= 0) {
									if (me->is_attackable(point - 1)) {
										point -= 1;
										ClearDrawScreen();
										redraw_battle(stage, enemy, size_enemy, players, size_players);
										draw_attackable_area(me, players, size_players, enemy, size_enemy);
										draw_attack_area(point, me);
									}
								}
								while (CheckHitKey(KEY_INPUT_LEFT)) {}
							}
							else if (CheckHitKey(KEY_INPUT_UP)) {
								if ((point / 10) - 1 >= 0) {
									if (me->is_attackable(point - 10)) {
										point -= 10;
										ClearDrawScreen();
										redraw_battle(stage, enemy, size_enemy, players, size_players);
										draw_attackable_area(me, players, size_players, enemy, size_enemy);
										draw_attack_area(point, me);
									}
								}
								while (CheckHitKey(KEY_INPUT_UP)) {}
							}
							else if (CheckHitKey(KEY_INPUT_DOWN)) {
								if ((point / 10) + 1 < 6) {
									if (me->is_attackable(point + 10)) {
										point += 10;
										ClearDrawScreen();
										redraw_battle(stage, enemy, size_enemy, players, size_players);
										draw_attackable_area(me, players, size_players, enemy, size_enemy);
										draw_attack_area(point, me);
									}
								}
								while (CheckHitKey(KEY_INPUT_DOWN)) {}
							}
						}
						while (CheckHitKey(KEY_INPUT_SPACE)) {}

						me->battle(point, me,size_players, enemy, size_enemy);
					}
					else if (select == 1) { //移動

						int movelimit = me->getDex();

						while (movelimit > 0 && CheckHitKey(KEY_INPUT_A) == 0) {
							if (CheckHitKey(KEY_INPUT_UP)) {
								if (me->move(0, -160, stage, enemy, size_enemy, players, size_players)) {
									movelimit--;
									ClearDrawScreen();
									redraw_battle(stage, enemy, size_enemy, players, size_players);
								}
								while (CheckHitKey(KEY_INPUT_UP)) {}
							}
							else if (CheckHitKey(KEY_INPUT_DOWN)) {
								if (me->move(0, -160, stage, enemy, size_enemy, players, size_players)) {
									movelimit--;
									ClearDrawScreen();
									redraw_battle(stage, enemy, size_enemy, players, size_players);
								}
								while (CheckHitKey(KEY_INPUT_DOWN)) {}
							}
							else if (CheckHitKey(KEY_INPUT_RIGHT)) {
								if (me->move(160, 0, stage, enemy, size_enemy, players, size_players)) {
									movelimit--;
									ClearDrawScreen();
									redraw_battle(stage, enemy, size_enemy, players, size_players);
								}
								while (CheckHitKey(KEY_INPUT_RIGHT)) {}
							}
							else if (CheckHitKey(KEY_INPUT_LEFT)) {
								if (me->move(-160, 0, stage, enemy, size_enemy, players, size_players)) {
									movelimit--;
									ClearDrawScreen();
									redraw_battle(stage, enemy, size_enemy, players, size_players);
								}
								while (CheckHitKey(KEY_INPUT_LEFT)) {}
							}
						}
					}
				}
				else if (side == 1) {
					DrawFormatString(100, 100, GetColor(0, 0, 0), "enemy_turn");
					WaitTimer(300);
				}
			}
		}
		else if (select_do == 1) { //逃げる場合
			if (GetRand(100) < 50) {
				DrawFormatString(100, 100, GetColor(0, 0, 0), "run");
				WaitTimer(150);
				is_loop = false;
			}
			else {
				DrawFormatString(100, 100, GetColor(0, 0, 0), "don't run");
				WaitTimer(150);
			}
		}
	}
	if (enemy->getHp() < 0) {
		DrawFormatString(100, 100, GetColor(0, 0, 0), "end");
		WaitTimer(150);
		is_loop = false;
	}

	InitGraph();
}



