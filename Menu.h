#pragma once
#include "PartyControl.h"

class Menu {
private:
	int mode;			//モード
						/*
						0 : main
						1 : item
						2 : equipment
						3 : magic
						4 : save
						5 : close
						*/
	int main_select;	//メインでの選択肢を特定する変数
	int item_select;	//アイテムでの選択肢を特定する変数
	int equipment_select; //装備での選択肢を特定する変数
	int magic_select;	//魔術での選択肢を特定する変数
	int save_select;	//セーブでの選択肢を特定する変数
	int step;			//描画用のstep変数
	int window_image;	//ウィンドウの画像
	int pointer_image;	//ポインターの画像
	int subwindw_image;
	int start;
	int sub_select;
	
	PartyControl* pc;

	int sound_enter;
	int sound_error;
	int sound_move;
	int sound_cancel;

public:
	Menu();
	Menu(PartyControl* p);
	bool Update();			//全体の更新
	bool updateMain();		//メイン
	bool updateItem();		//アイテム
	bool updateEquipment();	//装備
	bool updateMagic();		//魔術
	bool updateSave();		//セーブ
	bool closeWindow();		//ウィンドウを閉じる
};