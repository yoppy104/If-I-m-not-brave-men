#pragma once

class Menu {
private:
	/*
	0 : main
	1 : item
	2 : equipment
	3 : magic
	4 : save
	5 : close
	*/
	int mode;

	/*
	0 : start
	*/
	int step;

	int window_image;
	

public:
	Menu();
	bool Update();
	bool updateMain();
	bool updateItem();
	bool updateEquipment();
	bool updateMagic();
	bool updateSave();
	bool closeWindow();
};