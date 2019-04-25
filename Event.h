#pragma once
#include <vector>

using namespace std;

class Event {
protected:
	int id;
	int step;
	vector <char*> text;

	int text_box;
	int sound_enter;

public:
	Event();
	Event(int id);
	virtual bool Update();
};