#pragma once
#include <vector>

/*
概要 :	イベント処理を実装するBaseクラス
		継承して使用する予定
*/

class Event {
protected:
	int id;		//イベントID
	int step;	//イベントアニメーション用のフレーム数
	std::vector <char*> text;	//イベントのテキスト

	int text_box;		//テキストを表示する部分の画像
	int sound_enter;	//文字を送ったときの音

public:
	Event() = default;
	Event(int id);
	virtual bool Update();
};