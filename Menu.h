#pragma once

class Menu {
private:
	/*
	0 : main
	1 : item
	2 : equipment
	3 : magic
	4 : save
	*/
	int mode;

	/*
	0 : start
	*/
	int step;
	

public:
	Menu();
	bool Update();
	void updateMain();
	void updateItem();
	void updateEquipment();
	void updateMagic();
	void updateSave();
	void closeWindow();
};