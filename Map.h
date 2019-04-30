#pragma once
#include "NPC.h"
#include "Event.h"

//マップ一つ一つのクラス
class Map {
private:
	int		inf;			// この地点が何かの情報
	bool	isMove;		// 移動可能か
	bool	isEvent;		// イベントがあるかどうか
	bool	isNpc;			// npcがいるかどうか
	bool	isEncount;		// エンカウントするかどうか
	double	encountRate;	// 敵との遭遇率
	int		encountTable;	// この場所でエンカウントする敵のテーブルを指定するid
	shared_ptr<NPC>	npc;			// この場所にいるnpcの情報。
	shared_ptr<Event>	event;		// この場所で発生するイベント

public:
	//コンストラクタ
	Map() = default;
	Map(int data, bool is_event, bool is_npc, int table, shared_ptr<NPC> npc);

	//取得メソッド
	bool getIsMove() { return this->isMove && !this->isNpc; }
	bool getIsEvent() { return isEvent; }
	bool getIsNpc() { return isNpc; }
	bool getIsEncount() { return isEncount; }
	void setData(int data);
	void setIsEvent(bool is);
	void setNpc(bool isnt);
	void setNpc(shared_ptr<NPC> npc);
	shared_ptr<NPC> getNPC();
	void chatNPC();
	void setEvent(shared_ptr<Event> myevent);
	shared_ptr<Event> getEvent();
	void delEvent();
	void setTable(int table);
	double getRate() { return encountRate; }
	int getTable() { return encountTable; }
};