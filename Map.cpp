#include "Map.h"
#include "DxLib.h"

Map::Map(int data, bool isEvent, bool isNpc, int table, std::shared_ptr<NPC> npc) :
	isEncount(true),
	transform_map(UNDIFINED),
	transform_x(0),
	transform_y(0),
	is_transform(false)
{
	// データによって制御
	encountRate = 100;
	encountTable = table;
	inf = data;

	switch (data) {
	case 0: // 草原
		isMove = true;
		isEncount = true;
		encountRate = 0;
		is_move_enemy = true;
		break;
	case 1: // 地面
		isMove = true;
		isEncount = true;
		encountRate = 0;
		is_move_enemy = true;
		break;
	case 2: //森
		isMove = false;
		isEncount = false;
		encountRate = 0;
		is_move_enemy = false;
		break;
	case 3: //山岳
		isMove = false;
		isEncount = false;
		encountRate = 0;
		is_move_enemy = false;
		break;
	case 4: //海
		isMove = false;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 5: //小さい町
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 6: //大きな町
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 7: //城
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 8: //橋
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	}
	isEvent = isEvent;
	isNpc = isNpc;
	if (isNpc) {
		this->npc = npc;
	}
}

void Map::setData(int data) {
	inf = data;
	switch (data) {
	case 0: // 草原
		isMove = true;
		isEncount = true;
		encountRate = 0;
		is_move_enemy = true;
		break;
	case 1: // 地面
		isMove = true;
		isEncount = true;
		encountRate = 0;
		is_move_enemy = true;
		break;
	case 2: //森
		isMove = false;
		isEncount = true;
		encountRate = 0;
		is_move_enemy = false;
		break;
	case 3: //山岳
		isMove = false;
		isEncount = false;
		encountRate = 0;
		is_move_enemy = false;
		break;
	case 4: //海
		isMove = false;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 5: //小さい町
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 6: //大きな町
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 7: //城
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 8: //橋
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	}
}

void Map::setIsEvent(bool is) {
	isEvent = is;
}

void Map::setNpc(bool isnt) {
	isNpc = isnt;
}

void Map::setNpc(std::shared_ptr<NPC> npc) {
	isNpc = true;
	this->npc = npc;
}

std::shared_ptr<NPC> Map::getNPC() {
	return npc;
}

void Map::chatNPC() {
	npc->chat();
}

void Map::setEvent(std::shared_ptr<Event> myevent) {
	isEvent = true;
	event = myevent;
}

std::shared_ptr<Event> Map::getEvent() {
	if (isEvent) {
		return event;
	}
	else {
		return NULL;
	}
}

void Map::delEvent() {
	isEvent = false;
}

void Map::setTable(int table) {
	encountTable = table;
}