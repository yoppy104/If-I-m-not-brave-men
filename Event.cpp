#include "Event.h"
#include "M_Functions.h"
#include "DxLib.h"

Event::Event() {

}

Event::Event(int id) {
	this->id = id;
	this->step = 0;
}

void Event::message(int type) {
	DrawFormatString(100, 100, GetColor(255, 255, 255), "Test Event");
}

bool Event::Update() {
	this->message(0);
	if (Button(KEY_INPUT_SPACE)) {
		return true;
	}
	else {
		return false;
	}
}