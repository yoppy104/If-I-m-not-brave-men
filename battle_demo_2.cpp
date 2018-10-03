#include "DxLib.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "Equipment.h"
#include "Player.h"
#include "Enemy.h"
#include "draw.h"

using namespace std;

typedef uint8_t datatable;
typedef unsigned long long stagedata;
//komenntokakuyo

//本文
int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR pCmdLine, int CmdShow)
{

	SRand(time(NULL));

	ChangeWindowMode(true); // ウインドウモードに変更
	SetGraphMode(1920, 1200, 32); // ウィンドウサイズを指定
	SetMainWindowText("NotBraveman"); // ウィンドウタイトルを指定
	SetOutApplicationLogValidFlag(FALSE); // ログが出ないように設定

	if (DxLib_Init() == -1) // DXライブラリの初期化
	{
		return -1; // エラーを吐いたら終了
	}

	int enemy_image = LoadGraph("enemy.png"); // 敵の画像
	int player_image = LoadGraph("プレイヤー.png"); // プレイヤーの画像
	int frame_image = LoadGraph("battleframe.png"); // 攻撃範囲の選択用

	//ステージのデータ値
	stagedata stage = 0b1111111111111111111011111111111111111;

	//障害物の設定
	int block = 0;
	if (block != 0) {
		stagedata test = 1;
		for (int i = 0; i < block; i++) {
			int r = rand() % 36;
			stagedata key = pow(2, r);
			test |= key;
		}
		stage = ~(stage & test);
	}



	int battlemap_left = 496; // マップの左の座標
	int battlemap_top = 136; // マップの上の座標

	Equipment iron_sword(true, 10, 50, 1, -1, 42 ); // 装備のクラス

	Player allen("allen", 100, battlemap_left + 160 * 5, battlemap_top + 160 * 5, 10, 2, iron_sword, player_image, 50); // アレンの構造体定義

	Enemy slime("slime", 50, battlemap_left + 160 * 2, battlemap_top + 160 * 3, 2, 1, enemy_image); // スライムの構造体定義

	redraw_battle(stage, &slime, &allen); // 再描画

	SetFontSize(32); // フォントサイズの指定

	ProcessMessage(); // 割り込み処理をするときに必須

	int select;
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) { // escapeを入力したらゲーム終了
		select = 0; // 0:攻撃 1:いどう 2:アイテム 3:防御
		ClearDrawScreen();
		redraw_battle(stage, &slime, &allen);
		draw_command(select); //コマンド枠を描画

		// 行動の選択
		while (CheckHitKey(KEY_INPUT_SPACE) == 0) { // spaceを押したら決定
			if (CheckHitKey(KEY_INPUT_DOWN)) { // 下を押したらselectを+1
				if (select == 0) {
					select++;
					ClearDrawScreen();
					redraw_battle(stage, &slime, &allen);
					draw_command(select);
				}
				while(CheckHitKey(KEY_INPUT_DOWN)){}
			}
			else if (CheckHitKey(KEY_INPUT_UP)) { // 上を押したらselectを―1
				if (select == 1) {
					select--;
					ClearDrawScreen();
					redraw_battle(stage, &slime, &allen);
					draw_command(select);
				}
				while(CheckHitKey(KEY_INPUT_UP)){}
			}
		}
		while (CheckHitKey(KEY_INPUT_SPACE)) {}

		redraw_battle(stage, &slime, &allen);

		if (select == 0) { //通常攻撃
			int point = draw_attackable_area(allen, slime);
			draw_attack_area(point, allen);
			while(CheckHitKey(KEY_INPUT_SPACE) == 0){
				if (CheckHitKey(KEY_INPUT_RIGHT)) {
					if ((point % 10) + 1 < 6) {
						if (allen.is_attackable(point + 1)) {
							point += 1;
							ClearDrawScreen();
							redraw_battle(stage, &slime, &allen);
							draw_attackable_area(allen, slime);
							draw_attack_area(point, allen);
						}
					}
					while (CheckHitKey(KEY_INPUT_RIGHT)) {}
				}
				else if (CheckHitKey(KEY_INPUT_LEFT)) {
					if ((point % 10) - 1 >= 0) {
						if (allen.is_attackable(point - 1)) {
							point -= 1;
							ClearDrawScreen();
							redraw_battle(stage, &slime, &allen);
							draw_attackable_area(allen, slime);
							draw_attack_area(point, allen);
						}
					}
					while (CheckHitKey(KEY_INPUT_LEFT)) {}
				}
				else if (CheckHitKey(KEY_INPUT_UP)) {
					if ((point / 10) - 1 >= 0) {
						if (allen.is_attackable(point - 10)) {
							point -= 10;
							ClearDrawScreen();
							redraw_battle(stage, &slime, &allen);
							draw_attackable_area(allen, slime);
							draw_attack_area(point, allen);
						}
					}
					while (CheckHitKey(KEY_INPUT_UP)) {}
				}
				else if (CheckHitKey(KEY_INPUT_DOWN)) {
					if ((point / 10) + 1 < 6) {
						if (allen.is_attackable(point + 10)) {
							point += 10;
							ClearDrawScreen();
							redraw_battle(stage, &slime, &allen);
							draw_attackable_area(allen, slime);
							draw_attack_area(point, allen);
						}
					}
					while (CheckHitKey(KEY_INPUT_DOWN)) {}
				}
			}
			while(CheckHitKey(KEY_INPUT_SPACE)){}

			allen.battle(point, &allen, &slime);
		}
		else if (select == 1) { //移動

			int movelimit = allen.getDex();

			while (movelimit > 0 && CheckHitKey(KEY_INPUT_A) == 0) {
				if (CheckHitKey(KEY_INPUT_UP)) {
					if (allen.move(0, -160, stage, slime, allen)) {
						movelimit--;
						ClearDrawScreen();
						redraw_battle(stage, &slime, &allen);
					} 
					while (CheckHitKey(KEY_INPUT_UP)){}
				}
				else if (CheckHitKey(KEY_INPUT_DOWN)) {
					if (allen.move(0, 160, stage, slime, allen)) {
						movelimit--;
						ClearDrawScreen();
						redraw_battle(stage, &slime, &allen);
					}
					while (CheckHitKey(KEY_INPUT_DOWN)) {}
				}
				else if (CheckHitKey(KEY_INPUT_RIGHT)) {
					if (allen.move(160, 0, stage, slime, allen)) {
						movelimit--;
						ClearDrawScreen();
						redraw_battle(stage, &slime, &allen);
					}
					while (CheckHitKey(KEY_INPUT_RIGHT)) {}
				}
				else if (CheckHitKey(KEY_INPUT_LEFT)) {
					if (allen.move(-160, 0, stage, slime, allen)) {
						movelimit--;
						ClearDrawScreen();
						redraw_battle(stage, &slime, &allen);
					}
					while (CheckHitKey(KEY_INPUT_LEFT)) {}
				}
			}
		}
		if (slime.getHp() < 0) {
			DrawFormatString(100, 100, GetColor(0, 0, 0), "end");
			WaitTimer(150);
			return 0;
		}
	}

	InitGraph();
	DxLib_End(); // ＤＸライブラリ使用の終了処理
	return 0; // ソフトの終了
}



