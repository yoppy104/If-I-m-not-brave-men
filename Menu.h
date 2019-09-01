#pragma once
#include "PartyControll.h"
#include "IDs.h"

//現在のモードを定義している。
enum Mode {
	MAIN,
	ITEM,
	EQUIPMENT,
	MAGIC,
	SAVE,
	CLOSE
};

/*
概要 :	メニュー操作を定義するクラス
*/
class Menu {
private:
	using Image = struct {
		int window;
		int pointer;
		int subwindow;
	};

	using Sound = struct {
		int enter;
		int error;
		int move;
		int cancel;
	};

	Mode mode;
	int mainSelect;	//メインでの選択肢を特定する変数
	int itemSelect;	//アイテムでの選択肢を特定する変数
	int equipmentSelect; //装備での選択肢を特定する変数
	int magicSelect;	//魔術での選択肢を特定する変数
	int saveSelect;	//セーブでの選択肢を特定する変数
	int step;			//描画用のstep変数
	Image images;
	int start;
	int subSelect;

	bool is_select_value;
	int selected_value;
	
	std::weak_ptr<PartyControll> pc;

	Sound sounds;

public:
	Menu() = default;
	Menu(std::shared_ptr<PartyControll> p);
	bool Update();			//全体の更新
	bool updateMain();		//メイン
	bool updateItem();		//アイテム
	bool updateEquipment();	//装備
	bool updateMagic();		//魔術
	bool updateSave();		//セーブ
	bool closeWindow();		//ウィンドウを閉じる

	bool SelectValue(int max_value); //個数を選択するメソッド
};