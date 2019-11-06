#include <vector>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <memory>
#include "DxLib.h"
#include "IDs.h"
#include "M_Functions.h"
#include "MapControll.h"
#include "PartyControll.h"
#include "Battle_Stage.h"

using player_ptr = std::shared_ptr<Player> ;

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR pCmdLine, int CmdShow)
{
	ChangeWindowMode(true);	SetGraphMode(1920, 1200, 32);
	//SetGraphMode(1920, 1200, 32); // ウィンドウサイズを指定
	SetDrawArea(0, 0, 1920, 1200);
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);
	SetMainWindowText("IfNotBraveman"); // ウィンドウタイトルを指定
	SetOutApplicationLogValidFlag(FALSE); // ログが出ないように設定

	if (DxLib_Init() == -1) // DXライブラリの初期化
	{
		return -1; // エラーを吐いたら終了
	}

	SetFontSize(32); // フォントサイズの指定

	ProcessMessage(); // 割り込み処理をするときに必須

	SRand(time(NULL));

	// 音声ファイルの読み込み
	int main = LoadSoundMem("sounds\\SystemBGM\\Opening.mp3"); //メインテーマ
	ChangeVolumeSoundMem(100, main);

	//パーティーインスタンスを生成する。
	player_ptr allen(new Player(ALLEN, 496 + 160 * 5, 136 + 160 * 5));
	std::vector<player_ptr> players = { allen };
	std:: shared_ptr<PartyControll> pc(new PartyControll(players, 0, 1000));

	//バトルのインスタンスを生成する。
	std::unique_ptr<Battle_Stage> battle_stage(new Battle_Stage(pc));

	int mode = TITLE;

	//20 40
	std::unique_ptr<MapControll> mapc(new MapControll(1920, 1200, 20, 40, 1, players[0], pc));

	int image_title = LoadGraph("images\\BackGround\\タイトル1920 1200.png");

	mode = TITLE;

	int enemy_infomation = 0;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && Button(KEY_INPUT_ESCAPE) < 50) {
		SetDrawScreen(DX_SCREEN_BACK);
		gpUpdateKey();
		switch (mode) {
		case TITLE://タイトル画面
			if (!CheckSoundMem(main)) {
				PlaySoundMem(main, DX_PLAYTYPE_LOOP, TRUE);
			}
			DrawGraph(0, 0, image_title, TRUE);
			if (AnyButton()) {//任意のキーを押したら、マップ画面に遷移する。
				mode = MAP_NORMAL;
				StopSoundMem(main);
			}
			break;
		case MAP_NORMAL://マップ画面
			enemy_infomation = mapc->Update();
			if (enemy_infomation) {
				mode = BATTLE_START;
			}
			break;
		case BATTLE_START://バトル画面
			int battle = battle_stage->Battle_Update(enemy_infomation);
			if (battle == 1) {
				mode = MAP_NORMAL;
			}
			else if (battle == -1) {
				mode = TITLE;
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