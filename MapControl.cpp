#include "MapControl.h"
#include "DxLib.h"
#include <fstream>
#include <string>
#include "IDs.h"

using namespace std;

MapControl::MapControl() {

}

MapControl::MapControl(int x, int y, int map) {
	this->countFrame = 0;
	this->directionPlayer = 0;
	this->position_player[0] = x;
	this->position_player[1] = y;
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

void MapControl::show(int width, int height, Player* allen) {
	int x = -this->position_player[0]*64 + width/2;
	int y = -this->position_player[1]*64 + height/2;
	DrawGraph(x, y, this->image, TRUE);
	if (this->directionPlayer == 1 || this->directionPlayer == 0) {
		allen->draw_map(width/ 2, height / 2, (this->countFrame/10) % 2, this->directionPlayer);
	}
	else {
		allen->draw_map(width / 2, height / 2, (this->countFrame/10) % 4, this->directionPlayer);
	}
	this->countFrame++;
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
			if (is_npc) {
				this->maps[col][row]->setNpc(&npc);
			}
			else {
				this->maps[col][row]->setNpc(false);
			}
			if (is_event) {
				this->maps[col][row]->setEvent(&events);
			}
			else {
				this->maps[col][row]->setEvent(false);
			}
			this->maps[col][row]->setTable(table);
			col++;
				
		}
		++row;
	}
}

void MapControl::Update(int code) {
	switch (code) {
	case 0:
		if ((this->position_player[1]+1 < this->mapsize_h) && this->maps[position_player[0]][position_player[1]+1]->getIsMove()){
			this->position_player[1] += 1;
		}
		this->directionPlayer = 0;
		break;
	case 1:
		if ((this->position_player[1] - 1 >= 0) && this->maps[position_player[0]][position_player[1] - 1]->getIsMove()) {
			this->position_player[1] -= 1;
		}
		this->directionPlayer = 1;
		break;
	case 2:
		if ((this->position_player[0] - 1 >= 0) && this->maps[position_player[0]-1][position_player[1]]->getIsMove()) {
			this->position_player[0] -= 1;
		}
		this->directionPlayer = 2;
		break;
	case 3:
		if ((this->position_player[0] + 1 < this->mapsize_w) && this->maps[position_player[0] + 1][position_player[1]]->getIsMove()) {
			this->position_player[0] += 1;
		}
		this->directionPlayer = 3;
		break;
	}
}