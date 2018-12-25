#pragma once

class Event {
protected:
	int id;
	int step;
public:
	Event();
	Event(int id);
	virtual void message(int type);
	virtual bool Update();
};