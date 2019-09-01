#include "Map.h"
#include "DxLib.h"

Map::Map(int data, bool isEvent, bool isNpc, int table, std::shared_ptr<NPC> npc) :
	isEncount(true),
	transform_map(UNDIFINED),
	transform_x(0),
	transform_y(0),
	is_transform(false)
{
	// �f�[�^�ɂ���Đ���
	encountRate = 100;
	encountTable = table;
	inf = data;

	switch (data) {
	case 0: // ����
		isMove = true;
		isEncount = true;
		encountRate = 0;
		is_move_enemy = true;
		break;
	case 1: // �n��
		isMove = true;
		isEncount = true;
		encountRate = 0;
		is_move_enemy = true;
		break;
	case 2: //�X
		isMove = false;
		isEncount = false;
		encountRate = 0;
		is_move_enemy = false;
		break;
	case 3: //�R�x
		isMove = false;
		isEncount = false;
		encountRate = 0;
		is_move_enemy = false;
		break;
	case 4: //�C
		isMove = false;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 5: //��������
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 6: //�傫�Ȓ�
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 7: //��
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 8: //��
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
	case 0: // ����
		isMove = true;
		isEncount = true;
		encountRate = 0;
		is_move_enemy = true;
		break;
	case 1: // �n��
		isMove = true;
		isEncount = true;
		encountRate = 0;
		is_move_enemy = true;
		break;
	case 2: //�X
		isMove = false;
		isEncount = true;
		encountRate = 0;
		is_move_enemy = false;
		break;
	case 3: //�R�x
		isMove = false;
		isEncount = false;
		encountRate = 0;
		is_move_enemy = false;
		break;
	case 4: //�C
		isMove = false;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 5: //��������
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 6: //�傫�Ȓ�
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 7: //��
		isMove = true;
		isEncount = false;
		is_move_enemy = false;
		break;
	case 8: //��
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