#include "MapControll.h"
#include "DxLib.h"
#include <fstream>
#include <string>
#include "IDs.h"
#include "M_Functions.h"
#include "Cleark.h"
#include "Inn.h"
#include <stdlib.h>
#include <time.h>



MapControll::MapControll(int width, int height, int x, int y, int map, std::shared_ptr<Player> allen, std::shared_ptr<PartyControll> pc) :
	positionPlayer{ x, y },
	directionPlayer(FRONT),
	dispSize{ width, height },
	allen(allen),
	pc(pc),
	enemies{},
	encountable(false),
	count_encount(0)
{
	countFrame = 0;
	nowEvent = nullptr;
	isMove = true;
	isChat = false;
	isEvent = false;
	isMenu = false;

	
	menu = std::shared_ptr<Menu>(new Menu(pc));

	sounds.main = LoadSoundMem("sounds\\MapBGM\\bgm02.wav");
	ChangeVolumeSoundMem(165, sounds.main);

	createMap(MAP_NORMAL);

	sounds.walk = LoadSoundMem("sounds\\MapSE\\踏みしめる06.mp3");
	ChangeVolumeSoundMem(70, sounds.walk);
	sounds.error = LoadSoundMem("sounds\\System\\SE_error.wav");
	ChangeVolumeSoundMem(255, sounds.error);
	sounds.enter = LoadSoundMem("sounds\\System\\SE_enter.wav");	   
	/*
	for (int i = 0; i < 24; i++) {
		SRand(time(NULL));
		int x = GetRand(99);
		int y = GetRand(99);
		enemies.push_back(std::make_unique<Enemy>(Enemy(HORNRABIT, x, y)));
	}
	*/
	enemies.push_back(std::make_unique<Enemy>(Enemy(HORNRABIT, 25, 39)));
	enemies.push_back(std::make_unique<Enemy>(Enemy(HORNRABIT, 28, 42)));
	enemies.push_back(std::make_unique<Enemy>(Enemy(HORNRABIT, 25, 45)));
	enemies.push_back(std::make_unique<Enemy>(Enemy(HORNRABIT, 35, 50)));

}

MapControll::~MapControll() {
	maps.clear();
}

void MapControll::show() {	
	//マップ画像の左上の座標
	//プレイヤーのいる座標が中央に来るように計算
	int x = (-positionPlayer.x*64 + dispSize.width/2);
	int y = (-positionPlayer.y*64 + dispSize.height/2);
	DrawGraph(x, y, mapImage, TRUE);
	//プレイヤーを描画する。
	//上下と左右でコマ数が違うため分類
	if (!encountable) {
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 256);
	}
	switch (directionPlayer) {
	case 0:
	case 1:
		allen->draw_map(dispSize.width / 2, dispSize.height / 2, (countFrame / 10) % 2, directionPlayer);
		break;
	case 2:
	case 3:
		allen->draw_map(dispSize.width / 2, dispSize.height / 2, (countFrame / 10) % 4, directionPlayer);
		break;
	}
	if (!encountable) {
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	}
	//npcを描画する
	/*	todo : 画面外なら描画しない  */
	if (!npcs.empty()) {
		for (int i = 0; i < npcs.size(); i++) {
			npcs.at(i)->draw(x + (npcs.at(i)->getX()) * 64, y + (npcs.at(i)->getY()) * 64);
		}
	}

	if (!enemies.empty()) {
		for (auto itr = enemies.begin(); itr != enemies.end(); itr++) {
			int enemy_x = itr->get()->getX();
			int enemy_y = itr->get()->getY();
			itr->get()->DrawMap(x + enemy_x * 64, y + enemy_y * 64);
		}
	}
}

void MapControll::createMap(ID id) {

	std::string file_name; 

	maps.clear();
	npcs.clear();

	switch (id) {
	case MAP_NORMAL:
		file_name = "datas\\MapData\\worldmap.csv";
		mapImage = LoadGraph("images\\MapTile\\worldmap.png");
		mapSize.width = 100;
		mapSize.height = 100;
		break;
	case MAP_HAJIET:
		file_name = "datas\\MapData\\test_map.csv";
		mapImage = LoadGraph("images\\MapTile\\test_map.png");
		mapSize.width = 20;
		mapSize.height = 20;
		break;
	}

	for (int x = 0; x < mapSize.width; x++) {
		maps.push_back(*new std::vector<std::shared_ptr<Map>>);
		for (int y = 0; y < mapSize.height; y++) {
			std::shared_ptr<Map> temp(new Map());
			maps[x].push_back(temp);
		}
	}

	std::ifstream stream(file_name);
	std::string line;
	const std::string delim = ",";

	int row = 0;
	int col;
	int table = ENCOUNT_FIRST_NORMAL;

	//Splitの機構
	while (getline(stream, line)) {
		col = 0;
		for (std::string::size_type spos, epos = 0;
			(spos = line.find_first_not_of(delim, epos)) != std::string::npos;) {
			std::string token = line.substr(spos, (epos = line.find_first_of(delim, spos)) - spos);
			maps[col][row]->setData(stoi(token));
			maps[col][row]->setTable(table);
			col++;
		}
		++row;
	}

	if (id == MAP_NORMAL) {
		for (int x = 17; x < 21; x++) {
			for (int y = 36; y < 39; y++) {
				maps[x][y]->setTransform(MAP_HAJIET);
				maps[x][y]->setTransformPos(10, 18);
			}
		}
	}
	else if (id == MAP_HAJIET) {

		std::vector<std::string> text = { "買い物とかも実現はできてるから、見ていってね。", "あと槍を装備すると貫通攻撃もできるから試してみてね。" };
		std::shared_ptr<NPC> temp1(new NPC(5, 5, "モブ子", text, 1));
		maps[5][5]->setNpc(temp1);
		npcs.push_back(temp1);

		std::vector<std::string> text5 = { "メニューは実装してあるらしいぞ。","Mキーを押してみな。" };
		std::shared_ptr<NPC> temp5(new NPC(15, 5, "モブ男", text5, 0));
		maps[15][5]->setNpc(temp5);
		npcs.push_back(temp5);

		std::vector<std::string> text2 = { "ここは防具屋です","なにか見ていきますか？","ありがとうございました。" };
		std::vector<ID> items2 = { LEATHERARM, LEATHERCAP, LEATHERCHEST, LEATHERSHIELD };
		std::shared_ptr<NPC> temp2(new Cleark("防具屋", 5, 10, items2, text2, pc));
		maps[5][10]->setNpc(temp2);
		npcs.push_back(temp2);

		std::vector<std::string> text3 = { "ここは武器屋です","なにか見ていきますか？","ありがとうございました。" };
		std::vector<ID> items3 = { WOODSWORD, STONESWORD, STEALSWORD };
		std::shared_ptr<NPC> temp3(new Cleark("武器屋", 15, 10, items3, text3, pc));
		maps[15][10]->setNpc(temp3);
		npcs.push_back(temp3);

		std::vector<std::string> text4 = { "ここは宿屋です","全員で%dゼルとなります。泊っていきますか？","", "ありがとうございました。" };
		std::shared_ptr<NPC> temp4(new Inn(5, 15, "宿屋", text4, 10, pc));
		maps[5][15]->setNpc(temp4);
		npcs.push_back(temp4);

		std::vector<std::string> text6 = { "すこし、バグが残ってるかもだな。報告してくれるとうれしいな。" };
		std::shared_ptr<NPC> temp6(new NPC(15, 15, "パツキン", text6, 0));
		maps[15][15]->setNpc(temp6);
		npcs.push_back(temp6);


		for (int x = 8; x < 13; x++) {
			maps[x][19]->setTransform(MAP_NORMAL);
			maps[x][19]->setTransformPos(19, 39);
		}
	}

}

bool MapControll::CheckMoveEnemy(int x, int y) {
	if (x < 0 || y < 0) {
		return false;
	}
	if (x > maps.size() - 1 || y > maps[0].size() - 1) {
		return false;
	}

	return maps[x][y]->getIsMoveEnemy();
}

int MapControll::Update() {
	if (!CheckSoundMem(sounds.main)) {
		PlaySoundMem(sounds.main, DX_PLAYTYPE_LOOP, TRUE);
	}
	countFrame++;
	show();

	if (isMove) {

		int x_enemy, y_enemy;
		bool top, down, left, right;

		for (auto itr = enemies.begin(); itr != enemies.end(); itr++) {
			x_enemy = itr->get()->getX();
			y_enemy = itr->get()->getY();

			top = CheckMoveEnemy(x_enemy, y_enemy - 1);
			down = CheckMoveEnemy(x_enemy, y_enemy + 1);
			left = CheckMoveEnemy(x_enemy + 1, y_enemy);
			right = CheckMoveEnemy(x_enemy - 1, y_enemy);

			itr->get()->UpdateInMap(top, down, left, right);
		}

		//下方向への移動
		if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			directionPlayer = FRONT;
			if ((positionPlayer.y + 1 < mapSize.height) && maps[positionPlayer.x][positionPlayer.y + 1]->getIsMove()) {
				PlaySoundMem(sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				positionPlayer.y += 1;
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		//上方向への移動
		else if (Button(KEY_INPUT_UP) % 15 == 1) {
			directionPlayer = BACK;
			if ((positionPlayer.y - 1 >= 0) && maps[positionPlayer.x][positionPlayer.y - 1]->getIsMove()) {
				PlaySoundMem(sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				positionPlayer.y -= 1;
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		//左方向への移動
		else if (Button(KEY_INPUT_LEFT) % 15 == 1) {
			directionPlayer = LEFT;
			if ((positionPlayer.x - 1 >= 0) && maps[positionPlayer.x - 1][positionPlayer.y]->getIsMove()) {
				PlaySoundMem(sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				positionPlayer.x -= 1;
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		//右方向への移動
		else if (Button(KEY_INPUT_RIGHT) % 15 == 1) {
			directionPlayer = RIGHT;
			if ((positionPlayer.x + 1 < mapSize.width) && maps[positionPlayer.x + 1][positionPlayer.y]->getIsMove()) {
				PlaySoundMem(sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				positionPlayer.x += 1;
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		//話しかける
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			int point_x = 0;
			int point_y = 0;
			//NPCの方を調べる
			switch (directionPlayer) {
			case FRONT:
				point_x = positionPlayer.x;
				point_y = positionPlayer.y + 1;
				break;
			case BACK:
				point_x = positionPlayer.x;
				point_y = positionPlayer.y - 1;
				break;
			case LEFT:
				point_x = positionPlayer.x - 1;
				point_y = positionPlayer.y;
				break;
			case RIGHT:
				point_x = positionPlayer.x + 1;
				point_y = positionPlayer.y;
				break;
			}
			if (IsInMap(point_x, point_y)) {
				if (maps[point_x][point_y]->getIsNpc()) {
					isChat = true;
					isMove = false;
					maps[point_x][point_y]->getNPC()->change_direction(positionPlayer.x, positionPlayer.y);
					nowChat = maps[point_x][point_y]->getNPC();
				}
			}
		}
		//メニューを開く
		else if (Button(KEY_INPUT_M) == 1) {
			PlaySoundMem(sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			isMove = false;
			isMenu = true;
		}
		if (maps[positionPlayer.x][positionPlayer.y]->getIsEvent()) {
			nowEvent = maps[positionPlayer.x][positionPlayer.y]->getEvent();
			isMove = false;
			isEvent = true;
		}
	}
	//イベント実行中の処理
	else if (isEvent){
		if (nowEvent->Update()) {
			isMove = true;
			isEvent = false;
			nowEvent = nullptr;
		}
	}
	//会話中の処理
	else if (isChat) {
		if (nowChat->chat()) {
			isChat = false;
			isMove = true;
		}
	}
	//メニュー操作中の処理
	else if (isMenu) {
		int test = menu->Update();
		if (test) {
			if (test == 2) {

			}
			else {
				isMenu = false;
				isMove = true;
			}
		}
	}

	//マップの切り替え処理
	if (maps[positionPlayer.x][positionPlayer.y]->getIsTransform()) {
		int prot_x = positionPlayer.x;
		int prot_y = positionPlayer.y;
		positionPlayer.x = maps[prot_x][prot_y]->getTrasformX();
		positionPlayer.y = maps[prot_x][prot_y]->getTrasformY();

		createMap(maps[prot_x][prot_y]->getTransform());
	}

	//エンカウント判定値を返却する。
	return CheckTriggerEncount();
}

bool MapControll::CheckTriggerEncount() {
	if (encountable) {
		for (auto itr = enemies.begin(); itr != enemies.end(); itr++) {
			if (positionPlayer.x == itr->get()->getX() &&
				positionPlayer.y == itr->get()->getY()) {
				int id = itr->get()->getId();
				enemies.erase(itr);

				int next_x = GetRand(15) + 20;
				int next_y = GetRand(15) + 30;
				enemies.push_back(std::make_unique<Enemy>(Enemy(HORNRABIT, next_x, next_y)));

				encountable = false;
				return id;
			}
		}
	}
	else {
		count_encount++;
		if (count_encount > 100) {
			count_encount = 0;
			encountable = true;
		}
	}
	return false;
}

bool MapControll::IsInMap(int x, int y) {
	return (x >= 0 && x < mapSize.width) && (y >= 0 && y < mapSize.height);
}