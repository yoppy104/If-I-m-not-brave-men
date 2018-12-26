#pragma once

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
	int step;			//描画用のstep変数
	int window_image;	//ウィンドウの画像
	int pointer_image;	//ポインターの画像
	

public:
	Menu();
	bool Update();			//全体の更新
	bool updateMain();		//メイン
	bool updateItem();		//アイテム
	bool updateEquipment();	//装備
	bool updateMagic();		//魔術
	bool updateSave();		//セーブ
	bool closeWindow();		//ウィンドウを閉じる
};