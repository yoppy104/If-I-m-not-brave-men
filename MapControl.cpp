#include "MapControl.h"
#include "DxLib.h"
#include <fstream>
#include <string>
#include "IDs.h"

using namespace std;

MapControl::MapControl(int x, int y, int map) {
	this->position_player[0] = x;
	this->position_player[1] = y;
	switch (map) {
	case 0:
		this->image = LoadGraph("");
		for (int x = 0; x < 500; x++) {
			this->maps.push_back(*new vector <Map*>);
			for (int y = 0; y < 500; y++) {
				this->maps[x].push_back(new Map());
			}
		}
		break;
	case 1:
		this->image = LoadGraph("test_map.png");
		for (int x = 0; x < 20; x++) {
			this->maps.push_back(*new vector <Map*>);
			for (int y = 0; y < 20; y++) {
				this->maps[x].push_back(new Map());
			}
		}
	}
	this->createMap();
}

int MapControl::getX() {
	return this->position_player[0];
}

int MapControl::getY() {
	return this->position_player[1];
}

void MapControl::show(int dispsize[], Player* allen) {
	int x = -this->position_player[0]*64 + dispsize[0]/2;
	int y = -this->position_player[1]*64 + dispsize[1]/2;
	DrawGraph(x, y, this->image, TRUE);
	allen->draw_map(dispsize[0] / 2 - 32, dispsize[1] / 2 - 32, 0, 0);
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
	while (getline(stream, line)) {
		col = 0;
		for (string::size_type spos, epos = 0;
			(spos = line.find_first_not_of(delim, epos)) != string::npos;) {
			string token = line.substr(spos, (epos = line.find_first_of(delim, spos)) - spos);
			this->maps[row][col]->setData(stoi(token));
			this->maps[row][col]->setIsEvent(is_event);
			if (is_npc) {
				this->maps[row][col]->setNpc(is_npc);
			}
			else {
				this->maps[row][col]->setNpc(&npc);
			}
			this->maps[row][col]->setTable(table);
			col++;
				
		}
		++row;
	}
}