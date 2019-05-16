#include "Map.h"
#include "DxLib.h"

Map::Map(int data, bool isEvent, bool isNpc, int table, shared_ptr<NPC> npc) :
	isEncount(true)
{
	// �f�[�^�ɂ���Đ���
	encountRate = 0;
	encountTable = table;
	inf = data;

	switch (data) {
	case 0: // ����
		isMove = true;
		isEncount = true;
		encountRate = 0;
		break;
	case 1: // �n��
		isMove = true;
		isEncount = true;
		encountRate = 0;
		break;
	case 2: //�X
		isMove = true;
		isEncount = true;
		encountRate = 0;
		break;
	case 3: //�R�x
		isMove = false;
		isEncount = false;
		encountRate = 0;
		break;
	case 4: //�C
		isMove = false;
		isEncount = false;
		break;
	case 5: //��������
		isMove = true;
		isEncount = false;
		break;
	case 6: //�傫�Ȓ�
		isMove = true;
		isEncount = false;
		break;
	case 7: //��
		isMove = true;
		isEncount = false;
		break;
	case 8: //��
		isMove = true;
		isEncount = false;
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
		break;
	case 1: // �n��
		isMove = true;
		isEncount = true;
		encountRate = 0;
		break;
	case 2: //�X
		isMove = false;
		isEncount = false;
		break;
	case 3: //�R�x
		isMove = false;
		isEncount = false;
		break;
	case 4: //�C
		isMove = false;
		isEncount = false;
		break;
	case 5: //��������
		isMove = true;
		isEncount = false;
		break;
	case 6: //�傫�Ȓ�
		isMove = true;
		isEncount = false;
		break;
	case 7: //��
		isMove = true;
		isEncount = false;
		break;
	case 8: //��
		isMove = true;
		isEncount = false;
		break;
	}
}

void Map::setIsEvent(bool is) {
	isEvent = is;
}

void Map::setNpc(bool isnt) {
	isNpc = isnt;
}

void Map::setNpc(shared_ptr<NPC> npc) {
	isNpc = true;
	this->npc = npc;
}

shared_ptr<NPC> Map::getNPC() {
	return npc;
}

void Map::chatNPC() {
	npc->chat();
}

void Map::setEvent(shared_ptr<Event> myevent) {
	isEvent = true;
	event = myevent;
}

shared_ptr<Event> Map::getEvent() {
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