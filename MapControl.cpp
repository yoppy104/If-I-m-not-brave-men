#include "MapControl.h"
#include "DxLib.h"
#include <fstream>
#include <string>
#include "IDs.h"
#include "M_Functions.h"
#include "Cleark.h"
#include "Inn.h"
#include <stdlib.h>
#include <time.h>



MapControl::MapControl(int width, int height, int x, int y, int map, std::shared_ptr<Player> allen, std::shared_ptr<PartyControl> pc) :
	positionPlayer{ x, y },
	directionPlayer(FRONT),
	dispSize{ width, height },
	allen(allen),
	pc(pc)
{
	countFrame = 0;
	nowEvent = nullptr;
	isMove = true;
	isChat = false;
	isEvent = false;
	isMenu = false;

	
	menu = std::shared_ptr<Menu>(new Menu(pc));

	mapImage = LoadGraph("images\\worldmap.png");
	mapSize.width = 100;
	mapSize.height = 100;
	for (int x = 0; x < 100; x++) {
		maps.push_back(*new std::vector<std::shared_ptr<Map>>);
		for (int y = 0; y < 100; y++) {
			std::shared_ptr<Map> temp(new Map());
			maps[x].push_back(temp);
		}
	}

	sounds.main = LoadSoundMem("sounds\\00sougen.wav");
	ChangeVolumeSoundMem(165, sounds.main);
	createMap();

	//以下NPCの初期化
	std::vector<std::string> text = { "今回は戦闘と一緒にすることができなかったのよね。","買い物とかも実現はできてるから、見て言ってね。" };
	std::shared_ptr<NPC> temp1(new NPC(21, 40, "モブ子", text, 1));
	maps[21][40]->setNpc(temp1);
	npcs.push_back(temp1);

	std::vector<std::string> text5 = { "メニューは実装してあるらしいぞ。","Mキーを押してみな。" };
	std::shared_ptr<NPC> temp5(new NPC(28, 9, "モブ男", text5, 0));
	maps[28][9]->setNpc(temp5);
	npcs.push_back(temp5);

	std::vector<std::string> text2 = { "ここは防具屋です","なにか見ていきますか？","ありがとうございました。" };
	std::vector<ID> items2 = { LEATHERARM, LEATHERCAP, LEATHERCHEST, LEATHERSHIELD };
	std::shared_ptr<NPC> temp2(new Cleark("防具屋", 22, 40, items2, text2, pc));
	maps[22][40]->setNpc(temp2);
	npcs.push_back(temp2);

	std::vector<std::string> text3 = { "ここは武器屋です","なにか見ていきますか？","ありがとうございました。" };
	std::vector<ID> items3 = { WOODSWORD, STONESWORD, STEALSWORD };
	std::shared_ptr<NPC> temp3(new Cleark("武器屋", 23, 40, items3, text3, pc));
	maps[23][40]->setNpc(temp3);
	npcs.push_back(temp3);

	std::vector<std::string> text4 = { "ここは宿屋です","全員で%dゼルとなります。泊っていきますか？","", "ありがとうございました。" };
	std::shared_ptr<NPC> temp4(new Inn(24, 40, "宿屋", text4, 10, pc));
	maps[24][40]->setNpc(temp4);
	npcs.push_back(temp4);

	std::vector<std::string> text6 = { "同じディスクに戦闘だけのファイルも入ってるからやってみてくれよな。","なんで別々かって？聞かないでくれ" };
	std::shared_ptr<NPC> temp6(new NPC(19, 50, "パツキン", text6, 0));
	maps[19][50]->setNpc(temp6);
	npcs.push_back(temp6);
	//ここまでNPCの設定


	sounds.walk = LoadSoundMem("sounds\\踏みしめる06.mp3");
	ChangeVolumeSoundMem(70, sounds.walk);
	sounds.error = LoadSoundMem("sounds\\SE_error.wav");
	ChangeVolumeSoundMem(255, sounds.error);
	sounds.enter = LoadSoundMem("sounds\\SE_enter.wav");	   
}

MapControl::~MapControl() {
	maps.clear();
}

void MapControl::show() {	
	//マップ画像の左上の座標
	//プレイヤーのいる座標が中央に来るように計算
	int x = (-positionPlayer.x*64 + dispSize.width/2);
	int y = (-positionPlayer.y*64 + dispSize.height/2);
	DrawGraph(x, y, mapImage, TRUE);
	//プレイヤーを描画する。
	//上下と左右でコマ数が違うため分類
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
	//npcを描画する
	/*	todo : 画面外なら描画しない  */
	if (!npcs.empty()) {
		for (int i = 0; i < npcs.size(); i++) {
			npcs.at(i)->draw(x + (npcs.at(i)->getX()) * 64, y + (npcs.at(i)->getY()) * 64);
		}
	}
}

void MapControl::createMap() {
	std::ifstream stream("worldmap.csv");
	std::string line;
	const std::string delim = ",";

	int row = 0;
	int col;
	int table = ENCOUNT_FIRST_NORMAL;

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
}

int MapControl::Update() {
	if (!CheckSoundMem(sounds.main)) {
		PlaySoundMem(sounds.main, DX_PLAYTYPE_LOOP, TRUE);
	}
	countFrame++;
	show();
	if (isMove) {
		if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			directionPlayer = FRONT;
			if ((positionPlayer.y + 1 < mapSize.height) && maps[positionPlayer.x][positionPlayer.y + 1]->getIsMove()) {
				PlaySoundMem(sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				positionPlayer.y += 1;

				double r = rand() % 100;
				if (maps[positionPlayer.x][positionPlayer.y]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_UP) % 15 == 1) {
			directionPlayer = BACK;
			if ((positionPlayer.y - 1 >= 0) && maps[positionPlayer.x][positionPlayer.y - 1]->getIsMove()) {
				PlaySoundMem(sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				positionPlayer.y -= 1;

				double r = rand() % 100;
				if (maps[positionPlayer.x][positionPlayer.y]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_LEFT) % 15 == 1) {
			directionPlayer = LEFT;
			if ((positionPlayer.x - 1 >= 0) && maps[positionPlayer.x - 1][positionPlayer.y]->getIsMove()) {
				PlaySoundMem(sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				positionPlayer.x -= 1;

				double r = rand() % 100;
				if (maps[positionPlayer.x][positionPlayer.y]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_RIGHT) % 15 == 1) {
			directionPlayer = RIGHT;
			if ((positionPlayer.x + 1 < mapSize.width) && maps[positionPlayer.x + 1][positionPlayer.y]->getIsMove()) {
				PlaySoundMem(sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				positionPlayer.x += 1;

				double r = rand() % 100;
				if (maps[positionPlayer.x][positionPlayer.y]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			int point_x, point_y;
			switch (directionPlayer) {
			case 0:
				point_x = positionPlayer.x;
				point_y = positionPlayer.y + 1;
				break;
			case 1:
				point_x = positionPlayer.x;
				point_y = positionPlayer.y - 1;
				break;
			case 2:
				point_x = positionPlayer.x - 1;
				point_y = positionPlayer.y;
				break;
			case 3:
				point_x = positionPlayer.x + 1;
				point_y = positionPlayer.y;
				break;
			}
			if (maps[point_x][point_y]->getIsNpc()) {
				isChat = true;
				isMove = false;
				maps[point_x][point_y]->getNPC()->change_direction(positionPlayer.x, positionPlayer.y);
				nowChat = maps[point_x][point_y]->getNPC();
			}
		}
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
	else if (isEvent){
		if (nowEvent->Update()) {
			isMove = true;
			isEvent = false;
			nowEvent = nullptr;
		}
	}
	else if (isChat) {
		if (nowChat->chat()) {
			isChat = false;
			isMove = true;
		}
	}
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
	return false;
}