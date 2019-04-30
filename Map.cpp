#include "Map.h"
#include "DxLib.h"

Map::Map(int data, bool isEvent, bool isNpc, int table, shared_ptr<NPC> npc) {
	// データによって制御
	this->encountRate = 0;
	this->encountTable = table;
	this->inf = data;

	switch (data) {
	case 0: // 草原
		this->isMove = true;
		this->isEncount = true;
		this->encountRate = 0;
		break;
	case 1: // 地面
		this->isMove = true;
		this->isEncount = true;
		this->encountRate = 0;
		break;
	case 2: //森
		this->isMove = true;
		this->isEncount = true;
		this->encountRate = 0;
		break;
	case 3: //山岳
		this->isMove = false;
		this->isEncount = false;
		this->encountRate = 0;
		break;
	case 4: //海
		this->isMove = false;
		this->isEncount = false;
		break;
	case 5: //小さい町
		this->isMove = true;
		this->isEncount = false;
		break;
	case 6: //大きな町
		this->isMove = true;
		this->isEncount = false;
		break;
	case 7: //城
		this->isMove = true;
		this->isEncount = false;
		break;
	case 8: //橋
		this->isMove = true;
		this->isEncount = false;
		break;
	}
	this->isEvent = isEvent;
	this->isNpc = isNpc;
	if (isNpc) {
		this->npc = move(npc);
	}
}

void Map::setData(int data) {
	this->inf = data;
	switch (data) {
	case 0: // 草原
		this->isMove = true;
		this->isEncount = true;
		this->encountRate = 0;
		break;
	case 1: // 地面
		this->isMove = true;
		this->isEncount = true;
		this->encountRate = 0;
		break;
	case 2: //森
		this->isMove = false;
		this->isEncount = false;
		break;
	case 3: //山岳
		this->isMove = false;
		this->isEncount = false;
		break;
	case 4: //海
		this->isMove = false;
		this->isEncount = false;
		break;
	case 5: //小さい町
		this->isMove = true;
		this->isEncount = false;
		break;
	case 6: //大きな町
		this->isMove = true;
		this->isEncount = false;
		break;
	case 7: //城
		this->isMove = true;
		this->isEncount = false;
		break;
	case 8: //橋
		this->isMove = true;
		this->isEncount = false;
		break;
	}
}

void Map::setIsEvent(bool is) {
	this->isEvent = is;
}

void Map::setNpc(bool isnt) {
	this->isNpc = isnt;
}

void Map::setNpc(shared_ptr<NPC> npc) {
	this->isNpc = true;
	this->npc = move(npc);
}

shared_ptr<NPC> Map::getNPC() {
	return npc;
}

void Map::chatNPC() {
	this->npc->chat();
}

void Map::setEvent(shared_ptr<Event> myevent) {
	this->isEvent = true;
	this->event = move(myevent);
}

shared_ptr<Event> Map::getEvent() {
	if (this->isEvent) {
		return this->event;
	}
	else {
		return NULL;
	}
}

void Map::delEvent() {
	this->isEvent = false;
}

void Map::setTable(int table) {
	this->encountTable = table;
}