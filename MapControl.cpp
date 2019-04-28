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

MapControl::MapControl(int width, int height, int x, int y, int map, Player* allen, PartyControl* pc) {
	this->allen = allen;
	this->countFrame = 0;
	this->directionPlayer = 0;
	this->position_player[0] = x;
	this->dispsize_h = height;
	this->dispsize_w = width;
	this->disp_rate = dispsize_h / 1920.0;
	this->position_player[1] = y;
	this->now = NULL;
	this->now_chat = new NPC();
	this->is_move = true;
	this->is_chat = false;
	this->is_event = false;
	this->is_menu = false;
	this->pc = pc;
	this->menu = new Menu(pc);
	
	this->image = LoadGraph("worldmap.png");
	this->mapsize_w = 100;
	this->mapsize_h = 100;
	for (int x = 0; x < 100; x++) {
		this->maps.push_back(*new vector <Map*>);
		for (int y = 0; y < 100; y++) {
			this->maps[x].push_back(new Map());
		}
	}
	this->sound_main = LoadSoundMem("00sougen.wav");
	ChangeVolumeSoundMem(165, this->sound_main);
	this->createMap();

	vector<string> text = { "今回は戦闘と一緒にすることができなかったのよね。","買い物とかも実現はできてるから、見て言ってね。" };
	NPC* temp = new NPC(21, 40, "モブ子", text, 1);
	this->maps[21][40]->setNpc(temp);
	this->npcs.push_back(temp);

	vector<string> text5 = { "メニューは実装してあるらしいぞ。","Mキーを押してみな。" };
	NPC* temp5 = new NPC(28, 9, "モブ男", text5, 0);
	this->maps[28][9]->setNpc(temp5);
	this->npcs.push_back(temp5);

	vector<string> text2 = { "ここは防具屋です","なにか見ていきますか？","ありがとうございました。" };
	vector<Item*> items2 = { new LeatherCap(), new LeatherArm(), new LeatherChest(), new LeatherSheild() };
	NPC* temp2 = new Cleark("防具屋", 22, 40, items2, text2, this->pc);
	this->maps[22][40]->setNpc(temp2);
	this->npcs.push_back(temp2);

	vector<string> text3 = { "ここは武器屋です","なにか見ていきますか？","ありがとうございました。" };
	vector<Item*> items3 = { new WoodSword(), new StoneSword(), new StealSword() };
	NPC* temp3 = new Cleark("武器屋", 23, 40, items3, text3, this->pc);
	this->maps[23][40]->setNpc(temp3);
	this->npcs.push_back(temp3);

	vector<string> text4 = { "ここは宿屋です","全員で%dゼルとなります。泊っていきますか？","", "ありがとうございました。" };
	NPC* temp4 = new Inn(24, 40, "宿屋", text4, 10, this->pc);
	this->maps[24][40]->setNpc(temp4);
	this->npcs.push_back(temp4);

	vector<string> text6 = { "同じディスクに戦闘だけのファイルも入ってるからやってみてくれよな。","なんで別々かって？聞かないでくれ" };
	NPC* temp6 = new NPC(19, 50, "パツキン", text6, 0);
	this->maps[19][50]->setNpc(temp6);
	this->npcs.push_back(temp6);

	this->sound_walk = LoadSoundMem("踏みしめる06.mp3");
	ChangeVolumeSoundMem(70, this->sound_walk);
	this->sound_error = LoadSoundMem("SE_error.wav");
	ChangeVolumeSoundMem(255, this->sound_error);
	this->sound_enter = LoadSoundMem("SE_enter.wav");


}

MapControl::~MapControl() {
	for (int i = 0; i < this->maps.size(); i++) {
		for (int j = 0; j < this->maps[i].size(); j++) {
			delete this->maps[i][j];
		}
	}
	
}
int MapControl::getX() {
	return this->position_player[0];
}

int MapControl::getY() {
	return this->position_player[1];
}

void MapControl::show() {
	int x = (-this->position_player[0]*64 + this->dispsize_w/2);
	int y = (-this->position_player[1]*64 + this->dispsize_h/2);
	DrawExtendGraph(x, y, x + (64 * this->mapsize_w), y + (64 * this->mapsize_h), this->image, TRUE);
	if (this->directionPlayer == 1 || this->directionPlayer == 0) {
		this->allen->draw_map(this->dispsize_w / 2, this->dispsize_h / 2, (this->countFrame/10) % 2, this->directionPlayer);
	}
	else {
		this->allen->draw_map(this->dispsize_w / 2, this->dispsize_h / 2, (this->countFrame/10) % 4, this->directionPlayer);
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
	if (!CheckSoundMem(this->sound_main)) {
		PlaySoundMem(this->sound_main, DX_PLAYTYPE_LOOP, TRUE);
	}
	this->show();
	if (this->is_move) {
		if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			this->directionPlayer = 0;
			if ((this->position_player[1] + 1 < this->mapsize_h) && this->maps[position_player[0]][position_player[1] + 1]->getIsMove()) {
				PlaySoundMem(this->sound_walk, DX_PLAYTYPE_BACK, TRUE);
				this->position_player[1] += 1;

				double r = rand() % 100;
				if (this->maps[this->position_player[0]][position_player[1]]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_UP) % 15 == 1) {
			this->directionPlayer = 1;
			if ((this->position_player[1] - 1 >= 0) && this->maps[position_player[0]][position_player[1] - 1]->getIsMove()) {
				PlaySoundMem(this->sound_walk, DX_PLAYTYPE_BACK, TRUE);
				this->position_player[1] -= 1;

				double r = rand() % 100;
				if (this->maps[this->position_player[0]][position_player[1]]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_LEFT) % 15 == 1) {
			this->directionPlayer = 2;
			if ((this->position_player[0] - 1 >= 0) && this->maps[position_player[0] - 1][position_player[1]]->getIsMove()) {
				PlaySoundMem(this->sound_walk, DX_PLAYTYPE_BACK, TRUE);
				this->position_player[0] -= 1;

				double r = rand() % 100;
				if (this->maps[this->position_player[0]][position_player[1]]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_RIGHT) % 15 == 1) {
			this->directionPlayer = 3;
			if ((this->position_player[0] + 1 < this->mapsize_w) && this->maps[position_player[0] + 1][position_player[1]]->getIsMove()) {
				PlaySoundMem(this->sound_walk, DX_PLAYTYPE_BACK, TRUE);
				this->position_player[0] += 1;

				double r = rand() % 100;
				if (this->maps[this->position_player[0]][position_player[1]]->getRate() > r) {
					return true;
				}
			}
			else {
				PlaySoundMem(this->sound_error, DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
			PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
			int point_x, point_y;
			switch (this->directionPlayer) {
			case 0:
				point_x = this->position_player[0];
				point_y = this->position_player[1] + 1;
				break;
			case 1:
				point_x = this->position_player[0];
				point_y = this->position_player[1] - 1;
				break;
			case 2:
				point_x = this->position_player[0] - 1;
				point_y = this->position_player[1];
				break;
			case 3:
				point_x = this->position_player[0] + 1;
				point_y = this->position_player[1];
				break;
			}
			if (this->maps[point_x][point_y]->getIsNpc()) {
				this->is_chat = true;
				this->is_move = false;
				this->maps[point_x][point_y]->getNPC()->change_direction(this->position_player[0], this->position_player[1]);
				this->now_chat = this->maps[point_x][point_y]->getNPC();
			}
		}
		else if (Button(KEY_INPUT_M) == 1) {
			PlaySoundMem(this->sound_enter, DX_PLAYTYPE_BACK, TRUE);
			this->is_move = false;
			this->is_menu = true;
		}
		if (this->maps[this->position_player[0]][this->position_player[1]]->getIsEvent()) {
			this->now = this->maps[this->position_player[0]][this->position_player[1]]->getEvent();
			this->is_move = false;
			this->is_event = true;
		}
	}
	else if (this->is_event){
		if (this->now->Update()) {
			this->is_move = true;
			this->is_event = false;
			this->now = NULL;
		}
	}
	else if (this->is_chat) {
		if (this->now_chat->chat()) {
			this->is_chat = false;
			this->is_move = true;
		}
	}
	else if (this->is_menu) {
		int test = this->menu->Update();
		if (test) {
			if (test == 2) {

			}
			else {
				this->is_menu = false;
				this->is_move = true;
			}
		}
	}
	return false;
}