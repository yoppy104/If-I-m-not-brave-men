#pragma once
#include "vector"
#include "Player.h"
#include "Enemy.h"
/*
void Battle(Player** players, int size_players);*/

using namespace std;
typedef unsigned long long stagedata;

class Battle {
private:
	vector <Enemy*> enemys; //エネミーベクター
	vector <Player*> players; //プレイヤーベクター
	stagedata stage; //ステージ
	int select; //選択番号
	int next_player; //次のプレイヤーのインデックス
	int next_enemy; //次のエネミーのインデックス
	Character* turn_character; //ターンのキャラクター

	//描画関数
	void draw_command_do(); //全体の行動のコマンドを描画
	void draw_command(); //単体の行動のコマンドを描画

	//画像
	int command_image; //コマンド部分の画像
	int point_image; //ポインタの画像
	//プレイヤーのステータスを表示する部分の画像
	int playerpanel_image_blue;
	int playerpanel_image_red;
	int playerpanel_image_gray;
	int background; // 背景画像

public:
	Battle(); //コンストラクタ
	Battle(vector <Player*> player); //コンストラクタ
	~Battle(); //デストラクタ

	vector <Enemy*> getEnemys(); //エネミー配列を返す
	Enemy* getEnemy(int index); //エネミー単体のポインタを返す。
	int getNumEnemys(); //エネミーの総数を返す。
	int getSelect(); //select変数を返す。

	void minusSelect(); //select変数を-1
	void plusSelect(); //select変数を+1

	void Update(int mode); //描画等の更新
	void changeNextCharacter(); //次のキャラクターを更新
	void select_init_(); //select変数を初期化

	int select_do_player();
};