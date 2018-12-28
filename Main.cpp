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
	ChangeWindowMode(true); // ウインドウモードに変更
	SetGraphMode(1920, 1200, 32); // ウィンドウサイズを指定
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


	WoodSword* iron_sword(); // 装備のクラス
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
	int title_image = LoadGraph("タイトル1920 1200.png");

	// 音声ファイルの読み込み
	int battle_bgm = LoadSoundMem("nomal-battle.wav"); //バトルBGM
	int button_se = LoadSoundMem("ピコ！.mp3"); //ボタン操作音
	int walk_se = LoadSoundMem("足音・草原を走る.mp3"); //歩行音
	int move_slime_se = LoadSoundMem("ドロドロが落ちる.mp3"); //スライムの移動音
	int attack_slime_se = LoadSoundMem("手足・殴る、蹴る10.mp3"); //スライムの攻撃音
	int sound_cancel = LoadSoundMem("ボタン音44.mp3"); //キャンセル音
	int sound_define = LoadSoundMem("ボタン音14.mp3"); //決定音
	int main = LoadSoundMem("main(仮)4_17.wav"); //メインテーマ


	Allen allen("アレン", 496 + 160 * 5, 136 + 160 * 5, 20, 6, 3, 6, 5, WoodSword(), allen_image, 10, allen_image_dead); // アレンの構造体定義
	fstream file;
	file.open("allendata.dat", ios::binary | ios::in);
	file.read((char*)&allen, sizeof(allen));
	file.close();
	/*
	Rain rain("レイン", 496 + 160 * 4, 136 + 160 * 5, 15, 4, 4, 10, 3, WoodSword(), rain_image, rain_image_dead); // レインの構造体定義
	Craig craig("クレイグ", 496 + 160 * 0, 136 + 160 * 5, 25, 10, 7, 0, 2, WoodSword(), craig_image, craig_image_dead); // クレイグの構造体定義
	Imitia imitia("イミティア", 496 + 160 * 1, 136 + 160 * 5, 20, 6, 8, 7, 6, WoodSword(), imitia_image, imitia_image_dead); // イミティアの構造体定義
	*/
	vector <Player*> players = { &allen };
	/*
	for (int i = 1; i < players.size(); i++) {
		int j = i;
		while (j > 0 && players[j]->getDex() > players[j - 1]->getDex()) {
			Player* t = players[j - 1];
			players[j - 1] = players[j];
			players[j] = t;
		}
	}
	*/
	PartyControl pc(players, 0, 100);
	/*
	fstream file;
	file.open("savedata.dat", ios::binary | ios::in);
	file.read((char*)&pc, sizeof(pc));
	file.close();
	*/
	int enemy_image = LoadGraph("スライム.png"); // 敵の画像
	int enemy_image_dead = LoadGraph("スライムdead.png");

	//ステージのデータ値
	stagedata stage = 0b1111111111111111111111111111111111111;

	int battlemap_left = 496; // マップの左の座標
	int battlemap_top = 136; // マップの上の座標

	int count_dead_players = 0;
	int count_dead_enemy = 0;

	int mode = TITLE;
	int drawmode = 0;

	Battle* battle;

	int click_stepframe = 30;

	mapc = MapControl(1920, 1200, 6, 5, 1, players[0], pc);
	
	file.open("savedata.dat", ios::binary | ios::in);
	file.read((char*)&mapc, sizeof(mapc));
	file.close();
	

	while (!CheckHitKey(KEY_INPUT_ESCAPE) && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		SetDrawScreen(DX_SCREEN_BACK);
		gpUpdateKey();
		mapc.Update();
	}

	file.open("savedata.dat", ios::binary | ios::out);
	file.write((char*)&mapc, sizeof(mapc));
	file.close();
	file.open("allendata.dat", ios::binary | ios::out);
	file.write((char*)players[0], sizeof(mapc));
	file.close();

	DxLib_End(); // ＤＸライブラリ使用の終了処理
	return 0; // ソフトの終了
}