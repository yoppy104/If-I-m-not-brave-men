#include "DxLib.h"
#include "Battle.h" 
#include "Player.h"
#include "Allen.h"
#include "Craig.h"
#include "Imitia.h"
#include "Rain.h"
#include "Weapon.h"
#include "FireBall.h"

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

	Weapon iron_sword(12, 50, 1, 1, 11); // 装備のクラス
	Weapon wood_bow(8, 50, 1, 2, 11); // 装備のクラス
	Weapon big_axe(15, 50, 1, 1, 11); // 装備のクラス
	Weapon iron_spear(10, 50, 1, 1, 21); // 装備のクラス

	int allen_image = LoadGraph("剣士アレン立ち.png"); //アレンの画像
	int rain_image = LoadGraph("槍レイン立ち.png"); //レインの画像
	int craig_image = LoadGraph("斧クレイグ立ち.png"); //クレイグの画像
	int imitia_image = LoadGraph("弓イミティア立ち.png"); //イミティアの画像

	Allen allen("アレン", 496 + 160 * 5, 136 + 160 * 5, 20, 7, 3, 6, 5, iron_sword, allen_image, 10); // アレンの構造体定義
	Rain rain("レイン", 496 + 160 * 4, 136 + 160 * 5, 15, 4, 2, 10, 3, iron_spear, rain_image); // レインの構造体定義
	Craig craig("クレイグ", 496 + 160 * 0, 136 + 160 * 5, 25, 10, 10, 0, 2, big_axe, craig_image); // クレイグの構造体定義
	Imitia imitia("イミティア", 496 + 160 * 1, 136 + 160 * 5, 20, 6, 8, 7, 6, wood_bow, imitia_image); // イミティアの構造体定義
	Player* players[] = { &allen, &rain, &craig, &imitia };
	int size_players = sizeof(players) / sizeof(players[0]);
	for (int i = 1; i < size_players; i++) {
		int j = i;
		while (j > 0 && players[j]->getDex() > players[j - 1]->getDex()) {
			Player* t = players[j - 1];
			players[j - 1] = players[j];
			players[j] = t;
		}
	}

	Battle(players, size_players);



	DxLib_End(); // ＤＸライブラリ使用の終了処理
	return 0; // ソフトの終了
}