#include "MapControl.h"
#include "DxLib.h"
#include <fstream>
#include <string>
#include "IDs.h"
#include "M_Functions.h"

using namespace std;

MapControl::MapControl() {

}

MapControl::MapControl(int width, int height, int x, int y, int map, Player* allen) {
	this->allen = allen;
	this->countFrame = 0;
	this->directionPlayer = 0;
	this->position_player[0] = x;
	this->dispsize_h = height;
	this->dispsize_w = width;
	this->disp_rate = dispsize_h / 1920.0;
	this->position_player[1] = y;
	this->now = NULL;
	this->now_chat = NPC();
	this->is_move = true;
	this->is_chat = false;
	this->is_event = false;
	switch (map) {
	case 0:
		this->image = LoadGraph("");
		this->mapsize_w = 500;
		this->mapsize_h = 500;
		for (int x = 0; x < 500; x++) {
			this->maps.push_back(*new vector <Map*>);
			for (int y = 0; y < 500; y++) {
				this->maps[x].push_back(new Map());
			}
		}
		break;
	case 1:
		this->image = LoadGraph("test_map.png");
		this->mapsize_w = 20;
		this->mapsize_h = 20;
		for (int x = 0; x < 20; x++) {
			this->maps.push_back(*new vector <Map*>);
			for (int y = 0; y < 20; y++) {
				this->maps[x].push_back(new Map());
			}
		}
	}
	this->createMap();
}

MapControl::~MapControl() {

}
int MapControl::getX() {
	return this->position_player[0];
}

int MapControl::getY() {
	return this->position_player[1];
}

void MapControl::show() {
	int x = (-this->position_player[0]*64 * this->disp_rate + this->dispsize_w/2);
	int y = (-this->position_player[1]*64 * this->disp_rate + this->dispsize_h/2);
	DrawExtendGraph(x, y, x + (64 * this->mapsize_w) * this->disp_rate, y + (64 * this->mapsize_h) * this->disp_rate, this->image, TRUE);
	if (this->directionPlayer == 1 || this->directionPlayer == 0) {
		this->allen->draw_map(this->dispsize_w / 2, this->dispsize_h / 2, (this->countFrame/10) % 2, this->directionPlayer, this->disp_rate);
	}
	else {
		this->allen->draw_map(this->dispsize_w / 2, this->dispsize_h / 2, (this->countFrame/10) % 4, this->directionPlayer, this->disp_rate);
	}
	this->countFrame++;
	if (!this->npcs.empty()) {
		for (int i = 0; i < this->npcs.size(); i++) {
			this->npcs.at(i).draw(x + (this->npcs.at(i).getX() * 64) * this->disp_rate, y + (this->npcs.at(i).getY() * 64) * this->disp_rate, this->disp_rate);
		}
	}
}



void MapControl::createMap() {
	ifstream stream("test_map.csv");
	string line;
	const string delim = ",";

	int row = 0;
	int col;
	bool is_event = false;
	bool is_npc = false;
	int table = ENCOUNT_FIRST_NORMAL;
	NPC npc;
	Event events;
	while (getline(stream, line)) {
		col = 0;
		for (string::size_type spos, epos = 0;
			(spos = line.find_first_not_of(delim, epos)) != string::npos;) {
			string token = line.substr(spos, (epos = line.find_first_of(delim, spos)) - spos);
			this->maps[col][row]->setData(stoi(token));
			this->maps[col][row]->setIsEvent(is_event);
			if (col == 11 && row == 6) {
				is_npc = true;
				npc = NPC(11, 6, "テスト君");
			}
			if (is_npc) {
				this->maps[col][row]->setNpc(&npc);
				this->npcs.push_back(npc);
			}
			else {
				this->maps[col][row]->setNpc(false);
			}
			if (col == 10 && row == 5) {
				is_event = true;
				events = Event();
			}
			if (is_event) {
				this->maps[col][row]->setEvent(&events);
			}
			else {
				this->maps[col][row]->setEvent(false);
			}
			this->maps[col][row]->setTable(table);
			col++;
			is_event = false;
			is_npc = false;
		}
		++row;
	}
}

void MapControl::Update() {
	if (this->is_move) {
		if (Button(KEY_INPUT_DOWN) % 15 == 1) {
			if ((this->position_player[1] + 1 < this->mapsize_h) && this->maps[position_player[0]][position_player[1] + 1]->getIsMove()) {
				this->position_player[1] += 1;
			}
			this->directionPlayer = 0;
		}
		else if (Button(KEY_INPUT_UP) % 15 == 1) {
			if ((this->position_player[1] - 1 >= 0) && this->maps[position_player[0]][position_player[1] - 1]->getIsMove()) {
				this->position_player[1] -= 1;
			}
			this->directionPlayer = 1;
		}
		else if (Button(KEY_INPUT_LEFT) % 15 == 1) {
			if ((this->position_player[0] - 1 >= 0) && this->maps[position_player[0] - 1][position_player[1]]->getIsMove()) {
				this->position_player[0] -= 1;
			}
			this->directionPlayer = 2;
		}
		else if (Button(KEY_INPUT_RIGHT) % 15 == 1) {
			if ((this->position_player[0] + 1 < this->mapsize_w) && this->maps[position_player[0] + 1][position_player[1]]->getIsMove()) {
				this->position_player[0] += 1;
			}
			this->directionPlayer = 3;
		}
		else if (Button(KEY_INPUT_SPACE) == 1) {
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
				this->now_chat = this->maps[point_x][point_y]->getNPC();
			}
		}
		if (this->maps[this->position_player[0]][this->position_player[1]]->getIsEvent()) {
			this->now = this->maps[this->position_player[0]][this->position_player[1]]->getEvent();
			this->is_move = false;
			this->is_event = true;
		}
		this->show();
	}
	else if (this->is_event){
		if (this->now.Update()) {
			this->is_move = true;
			this->is_event = false;
			this->now = NULL;
			this->maps[this->position_player[0]][this->position_player[1]]->delEvent();
		}
	}
	else if (this->is_chat) {
		if (now_chat.chat()) {
			this->is_chat = false;
			this->is_move = true;
		}
	}
}