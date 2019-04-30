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

using namespace std;

MapControl::MapControl() {

}

MapControl::MapControl(int width, int height, int x, int y, int map, const shared_ptr<Player> allen, const shared_ptr<PartyControl> pc) :
	positionPlayer{ x, y },
	directionPlayer(FRONT),
	dispSize{ height, width },
	dispRate(dispSize.height / 1920.0)
{
	this->allen = allen;
	this->countFrame = 0;
	this->now = NULL;
	this->isMove = true;
	this->isChat = false;
	this->isEvent = false;
	this->isMenu = false;
	this->pc = pc;

	shared_ptr<Menu> temp(new Menu(pc));
	menu = move(temp);

	this->image = LoadGraph("worldmap.png");
	this->mapSize.width = 100;
	this->mapSize.height = 100;
	for (int x = 0; x < 100; x++) {
		this->maps.push_back(*new vector<shared_ptr<Map>>);
		for (int y = 0; y < 100; y++) {
			shared_ptr<Map> temp(new Map());
			this->maps[x].push_back(temp);
		}
	}
	this->sounds.main = LoadSoundMem("00sougen.wav");
	ChangeVolumeSoundMem(165, this->sounds.main);
	this->createMap();

	vector<string> text = { "今回は戦闘と一緒にすることができなかったのよね。","買い物とかも実現はできてるから、見て言ってね。" };
	shared_ptr<NPC> temp1(new NPC(21, 40, "モブ子", text, 1));
	this->maps[21][40]->setNpc(temp1);
	this->npcs.push_back(temp1);

	vector<string> text5 = { "メニューは実装してあるらしいぞ。","Mキーを押してみな。" };
	shared_ptr<NPC> temp5(new NPC(28, 9, "モブ男", text5, 0));
	this->maps[28][9]->setNpc(temp5);
	this->npcs.push_back(temp5);

	vector<string> text2 = { "ここは防具屋です","なにか見ていきますか？","ありがとうございました。" };
	shared_ptr<Item> one(new LeatherCap());
	shared_ptr<Item> two(new LeatherArm());
	shared_ptr<Item> three(new LeatherChest());
	shared_ptr<Item> four(new LeatherSheild());
	vector<shared_ptr<Item>> items2 = { one, two, three, four };
	shared_ptr<NPC> temp2(new Cleark("防具屋", 22, 40, items2, text2, this->pc));
	this->maps[22][40]->setNpc(temp2);
	this->npcs.push_back(temp2);

	vector<string> text3 = { "ここは武器屋です","なにか見ていきますか？","ありがとうございました。" };
	shared_ptr<Weapon> onew(new WoodSword());
	shared_ptr<Weapon> twow(new StoneSword());
	shared_ptr<Weapon> threew(new StealSword());
	vector<shared_ptr<Item>> items3 = { onew, twow, threew };
	shared_ptr<NPC> temp3(new Cleark("武器屋", 23, 40, items3, text3, this->pc));
	this->maps[23][40]->setNpc(temp3);
	this->npcs.push_back(temp3);

	vector<string> text4 = { "ここは宿屋です","全員で%dゼルとなります。泊っていきますか？","", "ありがとうございました。" };
	shared_ptr<NPC> temp4(new Inn(24, 40, "宿屋", text4, 10, this->pc));
	this->maps[24][40]->setNpc(temp4);
	this->npcs.push_back(temp4);

	vector<string> text6 = { "同じディスクに戦闘だけのファイルも入ってるからやってみてくれよな。","なんで別々かって？聞かないでくれ" };
	shared_ptr<NPC> temp6(new NPC(19, 50, "パツキン", text6, 0));
	this->maps[19][50]->setNpc(temp6);
	this->npcs.push_back(temp6);

	this->sounds.walk = LoadSoundMem("踏みしめる06.mp3");
	ChangeVolumeSoundMem(70, this->sounds.walk);
	this->sounds.error = LoadSoundMem("SE_error.wav");
	ChangeVolumeSoundMem(255, this->sounds.error);
	this->sounds.enter = LoadSoundMem("SE_enter.wav");	   
}

MapControl::~MapControl() {
	maps.clear();
}

void MapControl::show() {
	int x = (-this->positionPlayer.x*64 + this->dispSize.width/2);
	int y = (-this->positionPlayer.y*64 + this->dispSize.height/2);
	DrawExtendGraph(x, y, x + (64 * this->mapSize.width), y + (64 * this->mapSize.height), this->image, TRUE);
	if (this->directionPlayer == 1 || this->directionPlayer == 0) {
		this->allen->draw_map(this->dispSize.width / 2, this->dispSize.height / 2, (this->countFrame/10) % 2, this->directionPlayer);
	}
	else {
		this->allen->draw_map(this->dispSize.width / 2, this->dispSize.height / 2, (this->countFrame/10) % 4, this->directionPlayer);
	}
	this->countFrame++;
	if (!this->npcs.empty()) {
		for (int i = 0; i < this->npcs.size(); i++) {
			this->npcs.at(i)->draw(x + (this->npcs.at(i)->getX()) * 64, y + (this->npcs.at(i)->getY()) * 64);
		}
	}
}

void MapControl::createMap() {
	ifstream stream("worldmap.csv");
	string line;
	const string delim = ",";

	int row = 0;
	int col;
	int table = ENCOUNT_FIRST_NORMAL;

	while (getline(stream, line)) {
		col = 0;
		for (string::size_type spos, epos = 0;
			(spos = line.find_first_not_of(delim, epos)) != string::npos;) {
			string token = line.substr(spos, (epos = line.find_first_of(delim, spos)) - spos);
			this->maps[col][row]->setData(stoi(token));
			this->maps[col][row]->setTable(table);
			col++;
		}
		++row;
	}
}

int MapControl::Update() {
	if (!CheckSoundMem(this->sounds.main)) {
		PlaySoundMem(this->sounds.main, DX_PLAYTYPE_LOOP, TRUE);
	}
	this->show();
	if (this->isMove) {
		if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			this->directionPlayer = FRONT;
			if ((this->positionPlayer.y + 1 < this->mapSize.height) && this->maps[positionPlayer.x][positionPlayer.y + 1]->getIsMove()) {
				PlaySoundMem(this->sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				this->positionPlayer.y += 1;

				double r = rand() % 100;
				if (this->maps[this->positionPlayer.x][positionPlayer.y]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_UP) % 15 == 1) {
			this->directionPlayer = BACK;
			if ((this->positionPlayer.y - 1 >= 0) && this->maps[positionPlayer.x][positionPlayer.y - 1]->getIsMove()) {
				PlaySoundMem(this->sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				this->positionPlayer.y -= 1;

				double r = rand() % 100;
				if (this->maps[this->positionPlayer.x][positionPlayer.y]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_LEFT) % 15 == 1) {
			this->directionPlayer = LEFT;
			if ((this->positionPlayer.x - 1 >= 0) && this->maps[positionPlayer.x - 1][positionPlayer.y]->getIsMove()) {
				PlaySoundMem(this->sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				this->positionPlayer.x -= 1;

				double r = rand() % 100;
				if (this->maps[this->positionPlayer.x][positionPlayer.y]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_RIGHT) % 15 == 1) {
			this->directionPlayer = RIGHT;
			if ((this->positionPlayer.x + 1 < this->mapSize.width) && this->maps[positionPlayer.x + 1][positionPlayer.y]->getIsMove()) {
				PlaySoundMem(this->sounds.walk, DX_PLAYTYPE_BACK, TRUE);
				this->positionPlayer.x += 1;

				double r = rand() % 100;
				if (this->maps[this->positionPlayer.x][positionPlayer.y]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(this->sounds.error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			int point_x, point_y;
			switch (this->directionPlayer) {
			case 0:
				point_x = this->positionPlayer.x;
				point_y = this->positionPlayer.y + 1;
				break;
			case 1:
				point_x = this->positionPlayer.x;
				point_y = this->positionPlayer.y - 1;
				break;
			case 2:
				point_x = this->positionPlayer.x - 1;
				point_y = this->positionPlayer.y;
				break;
			case 3:
				point_x = this->positionPlayer.x + 1;
				point_y = this->positionPlayer.y;
				break;
			}
			if (this->maps[point_x][point_y]->getIsNpc()) {
				this->isChat = true;
				this->isMove = false;
				this->maps[point_x][point_y]->getNPC()->change_direction(this->positionPlayer.x, this->positionPlayer.y);
				this->nowChat = this->maps[point_x][point_y]->getNPC();
			}
		}
		else if (Button(KEY_INPUT_M) == 1) {
			PlaySoundMem(this->sounds.enter, DX_PLAYTYPE_BACK, TRUE);
			this->isMove = false;
			this->isMenu = true;
		}
		if (this->maps[this->positionPlayer.x][this->positionPlayer.y]->getIsEvent()) {
			this->now = this->maps[this->positionPlayer.x][this->positionPlayer.y]->getEvent();
			this->isMove = false;
			this->isEvent = true;
		}
	}
	else if (this->isEvent){
		if (this->now->Update()) {
			this->isMove = true;
			this->isEvent = false;
			this->now = NULL;
		}
	}
	else if (this->isChat) {
		if (this->nowChat->chat()) {
			this->isChat = false;
			this->isMove = true;
		}
	}
	else if (this->isMenu) {
		int test = this->menu->Update();
		if (test) {
			if (test == 2) {

			}
			else {
				this->isMenu = false;
				this->isMove = true;
			}
		}
	}
	return false;
}