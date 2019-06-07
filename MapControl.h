#pragma once

#include "Map.h"
#include "Player.h"
#include "Menu.h"
#include <vector>

//プレイヤーの向いている方向
enum DirectionPlayer {
	FRONT,
	BACK,
	RIGHT,
	LEFT
};

//マップ制御用のクラス。Mapクラスを配列として管理する。
class MapControl {
private:

	//音声
	using Sound = struct {
		int main;
		int walk;
		int error;
		int enter;
	};

	//マップサイズ
	using MapSize = struct {
		int width;
		int height;
	};

	//ディスプレイサイズ
	using DispSize = struct {
		int width;
		int height;
	};

	// プレイヤーのマップ上での座標
	Vector positionPlayer;

	//プレイヤーの向いている方向
	DirectionPlayer directionPlayer;

	//マップの全体縦横のピクセル数
	MapSize mapSize;

	//ディスプレイの縦横のピクセル数
	DispSize dispSize;

	//現在のフレーム
	//アニメーション用
	int countFrame;

	//マップ情報をすべて格納したコンテナ
	std::vector <std::vector<std::shared_ptr<Map>>> maps;

	//プレイヤーの代表インスタンス
	std::shared_ptr<Player> allen;

	//現在実行中のイベント
	std::shared_ptr<Event> nowEvent;

	//マップに表示されるNPC
	std::vector<std::shared_ptr<NPC>> npcs;

	//移動可能かどうかのbool
	bool isMove;

	//イベントを処理中かどうかのbool
	bool isEvent;

	//会話を処理中かどうかのbool
	bool isChat;

	//メニューを処理中かどうかのbool
	bool isMenu;

	//マップの画像
	int mapImage;

	//現在会話中のNPC
	std::shared_ptr<NPC> nowChat;

	//メニュークラスのインスタンスを保持
	std::shared_ptr<Menu> menu;

	//パーティ管理クラスのインスタンスを保持
	std::shared_ptr<PartyControl> pc;

	Sound sounds;

public:
	MapControl() = default;
	MapControl(int width, int height, int x, int y, int map, std::shared_ptr<Player> allen, std::shared_ptr<PartyControl> pc);
	~MapControl();
	int getX() const { positionPlayer.x; }
	int getY() const { positionPlayer.y; }

	//更新メソッド
	int Update();

	//描画メソッド
	void show();

	//IDに合わせたマップを生成する
	void createMap();
};