#include "DxLib.h"
#include <vector>
#include <time.h>
#include "Battle.h" 
#include "Player.h"
#include "Allen.h"
#include "Craig.h"
#include "Imitia.h"
#include "Rain.h"
#include "Weapon.h"
#include "FireBall.h"
#include "IDs.h"
#include "M_Functions.h"
#include <iostream>
#include "Mathematic.h"
#include "MapControl.h"
#include "Items.h"
#include <cstdlib>
#include <fstream>

using namespace std;

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR pCmdLine, int CmdShow)
{
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
	SetGraphMode(1920, 1080, 32); // ウィンドウサイズを指定
	SetMainWindowText("NotBraveman"); // ウィンドウタイトルを指定
	SetOutApplicationLogValidFlag(FALSE); // ログが出ないように設定

	if (DxLib_Init() == -1) // DXライブラリの初期化
	{
		return -1; // エラーを吐いたら終了
	}

	SetFontSize(32); // フォントサイズの指定

	ProcessMessage(); // 割り込み処理をするときに必須

	SRand(time(NULL));

	//createMap();

	MapControl mapc;
	
	//画像ファイルの読み込み
	int allen_image = LoadGraph("剣士アレン立ち.png"); //アレンの画像
	int rain_image = LoadGraph("槍レイン立ち.png"); //レインの画像
	int craig_image = LoadGraph("斧クレイグ立ち.png"); //クレイグの画像
	int imitia_image = LoadGraph("弓イミティア立ち.png"); //イミティアの画像

	int allen_image_dead = LoadGraph("剣士アレンdead.png"); //アレンの画像
	int rain_image_dead = LoadGraph("槍レインdead.png"); //レインの画像
	int craig_image_dead = LoadGraph("斧クレイグdead.png"); //クレイグの画像
	int imitia_image_dead = LoadGraph("弓イミティアdead.png"); //イミティアの画像

	// 音声ファイルの読み込み
	int main = LoadSoundMem("main(仮)4_17.wav"); //メインテーマ

	Allen allen("アレン", 496 + 160 * 5, 136 + 160 * 5, 20, 6, 3, 6, 5, new WoodSword(), new NonHead(), new LeatherArm(), new LeatherChest(), new LeatherSheild(), allen_image, 10, allen_image_dead); // アレンの構造体定義

	vector <Player*> players;
	players.push_back(&allen);

	PartyControl* pc = new PartyControl(players, 0, 100);

	int count_dead_players = 0;
	int count_dead_enemy = 0;

	int mode = TITLE;

	int click_stepframe = 30;

	mapc = MapControl(1920, 1200, 6, 5, 1, players[0], pc);

	int image_title = LoadGraph("タイトル1920 1200.png");

	mode = TITLE;

	while (!CheckHitKey(KEY_INPUT_ESCAPE) && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
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
			if (mapc.Update()) {
				mode = BATTLE_START;
			}
			break;
		case BATTLE_START:
			DrawFormatString(100, 100, GetColor(255, 255, 255), "test encount");
			if (CheckHitKeyAll()) {
				mode = MAP_NORMAL;
			}
			break;
		}
		
	}

	InitSoundMem();
	DxLib_End(); // ＤＸライブラリ使用の終了処理
	return 0; // ソフトの終了
}