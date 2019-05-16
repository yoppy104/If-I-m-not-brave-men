#include "DxLib.h"
#include <vector>
#include <time.h>
#include "Player.h"
#include "Magic.h"
#include "IDs.h"
#include "M_Functions.h"
#include <iostream>
#include "MapControl.h"
#include "Item.h"
#include <cstdlib>
#include <fstream>
#include "Battle_Stage.h"

using namespace std;


int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR pCmdLine, int CmdShow)
{
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
	ChangeWindowMode(false);
	SetGraphMode(1920, 1200, 32); // ウィンドウサイズを指定
	SetMainWindowText("IfNotBraveman"); // ウィンドウタイトルを指定
	SetOutApplicationLogValidFlag(FALSE); // ログが出ないように設定

	if (DxLib_Init() == -1) // DXライブラリの初期化
	{
		return -1; // エラーを吐いたら終了
	}

	SetFontSize(32); // フォントサイズの指定

	ProcessMessage(); // 割り込み処理をするときに必須

	SRand(time(NULL));

	//createMap();

	MapControl* mapc;
	
	//画像ファイルの読み込み
	int allen_image = LoadGraph("剣士アレン立ち.png"); //アレンの画像

	int allen_image_dead = LoadGraph("剣士アレンdead.png"); //アレンの画像

	// 音声ファイルの読み込み
	int main = LoadSoundMem("00maintheme.wav"); //メインテーマ
	ChangeVolumeSoundMem(100, main);

	//Allen allen("アレン", 496 + 160 * 5, 136 + 160 * 5, 20, 10, 3, 6, 10, new WoodSword(), new NonHead(), new LeatherArm(), new LeatherChest(), new LeatherSheild(), allen_image, 10, allen_image_dead); // アレンの構造体定義

	shared_ptr<Player> allen(new Player(ALLEN, 496 + 160 * 5, 136 + 160 * 5));

	vector <shared_ptr<Player>> players;
	players.push_back(allen);

	shared_ptr<PartyControl> pc(new PartyControl(players, 0, 100));

	Battle_Stage* battle_stage = new Battle_Stage(pc);

	int mode = TITLE;

	//20 40
	mapc = new MapControl(1920, 1200, 20, 40, 1, players[0], pc);

	int image_title = LoadGraph("タイトル1920 1200.png");

	mode = TITLE;

	while (Button(KEY_INPUT_ESCAPE) < 50 && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		SetDrawScreen(DX_SCREEN_BACK);
		gpUpdateKey();
		switch (mode) {
		case TITLE:
			if (!CheckSoundMem(main)) {
				PlaySoundMem(main, DX_PLAYTYPE_LOOP, TRUE);
			}
			DrawGraph(0, 0, image_title, TRUE);
			if (CheckHitKeyAll()) {
				mode = MAP_NORMAL;
				StopSoundMem(main);
			}
			break;
		case MAP_NORMAL:
			if (mapc->Update()) {
				mode = BATTLE_START;
			}
			break;
		case BATTLE_START:
			if (battle_stage->Battle_Update()) {
				mode = MAP_NORMAL;
			}
			break;
		}
		
		if (Button(KEY_INPUT_ESCAPE) != 0) {
			DrawFormatString(10, 10, GetColor(0, 0, 0), "ゲームを終了します");
		}
	}

	InitSoundMem();
	DxLib_End(); // ＤＸライブラリ使用の終了処理
	return 0; // ソフトの終了
}
