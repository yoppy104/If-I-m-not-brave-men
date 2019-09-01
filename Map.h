#pragma once
#include "Npc.h"
#include "Event.h"
#include <memory>
#include "IDs.h"

/*
概要 : マップ一マス毎のクラス
*/

class Map {
private:
	int		inf;			// この地点が何かの情報
	bool	isMove;		// 移動可能か
	bool	isEvent;		// イベントがあるかどうか
	bool	isNpc;			// npcがいるかどうか
	bool	isEncount;		// エンカウントするかどうか
	double	encountRate;	// 敵との遭遇率
	int		encountTable;	// この場所でエンカウントする敵のテーブルを指定するid
	std::shared_ptr<NPC>	npc;			// この場所にいるnpcの情報。
	std::shared_ptr<Event>	event;		// この場所で発生するイベント
	bool	is_move_enemy;  //敵が移動可能かどうか

	bool is_transform;
	ID transform_map;
	int transform_x;
	int transform_y;

public:
	//コンストラクタ
	Map() = default;
	Map(int data, bool is_event, bool is_npc, int table, std::shared_ptr<NPC> npc);

	//取得メソッド
	bool getIsMove() { return isMove && !isNpc; }
	bool getIsMoveEnemy() { return is_move_enemy && !isNpc; }
	bool getIsEvent() { return isEvent; }
	bool getIsNpc() { return isNpc; }
	bool getIsEncount() { return isEncount; }
	void setData(int data);
	void setIsEvent(bool is);
	void setNpc(bool isnt);
	void setNpc(std::shared_ptr<NPC> npc);
	std::shared_ptr<NPC> getNPC();
	void chatNPC();
	void setEvent(std::shared_ptr<Event> myevent);
	std::shared_ptr<Event> getEvent();
	void delEvent();
	void setTable(int table);
	double getRate() { return encountRate; }
	int getTable() { return encountTable; }
	void setTransform(ID id) { transform_map = id; }
	void setTransformPos(int x, int y) { is_transform = true; transform_x = x; transform_y = y; }
	int getTrasformX() { return transform_x; }
	int getTrasformY() { return transform_y; }
	bool getIsTransform() { return is_transform; }
	ID getTransform() { return transform_map; }
};