#pragma once

class NPC {
private:
	char name[128];
	
public:
	NPC();
	NPC(char name[]);
	void getName(int x, int y);
	virtual void chat();
};