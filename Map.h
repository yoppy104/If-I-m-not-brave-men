#pragma once
#include "NPC.h"

//マップ一つ一つのクラス
class Map {
private:
	int		inf;			// この地点が何かの情報
	bool	is_move;		// 移動可能か
	bool	is_event;		// イベントがあるかどうか
	bool	is_npc;			// npcがいるかどうか
	bool	is_encount;		// エンカウントするかどうか
	double	encount_rate;	// 敵との遭遇率
	int		encount_table;	// この場所でエンカウントする敵のテーブルを指定するid
	NPC		npc;			// この場所にいるnpcの情報。

public:
	//コンストラクタ
	Map();
	Map(int data, bool is_event, bool is_npc, int table, NPC npc);

	//取得メソッド
	bool getIsMove();
	bool getIsEvent();
	bool getIsNpc();
	bool getIsEncount();
	void setData(int data);
	void setIsEvent(bool is);
	void setNpc(bool isnt);
	void setNpc(NPC* npc);
	void setTable(int table);
	double getRate();
	int getTable();
};