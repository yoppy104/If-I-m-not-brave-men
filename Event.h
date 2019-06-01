#pragma once
#include <vector>



class Event {
protected:
	int id;
	int step;
	std::vector <char*> text;

	int text_box;
	int sound_enter;

public:
	Event() = default;
	Event(int id);
	virtual bool Update();
};