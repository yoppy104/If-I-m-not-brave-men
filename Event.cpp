#include "Event.h"
#include "DxLib.h"

Event::Event() {

}

Event::Event(int id) {
	this->id = id;
	this->step = 0;
}

void Event::message(int type) {
	DrawFormatString(100, 100, GetColor(0, 0, 0), "Test Event");
}

void Event::Update() {
	this->message(0);
}