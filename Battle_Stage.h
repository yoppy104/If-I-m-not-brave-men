#pragma once
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <memory>
#include <algorithm>
#include "DxLib.h"
#include "M_Functions.h"
#include "PartyControl.h"
#include "Enemy.h"

class Battle_Stage
{
	bool is_first_time;
	bool troutCursol;
	int charaforcus;
	int enemyforcus;
	int scene;
	int number_of_character;
	bool enemyturn;
	bool AfterRunAsk;
	int Anime_frame;
	bool RunFail;
	int Random;
	bool Battle_End;


	int dropEXP;
	int Dropgill;
	
	std::vector<int> sort;
	std::vector<bool> is_enemy;


	int B_Panel, B_BG, B_Window, B_Statuswindow, B_Cursol, B_Frame ,CanMoveTrout,Danger,result,heal[8];//グラフィックハンドルたち
	int win, nomal, sword, punch, run_se, enemies_death;
	Player locate[6][6];//キャラクターたちの座標管理とかに用いる
	std::vector<player_ptr> yushas;
	std::vector<int> yushaLocateX;
	std::vector<int> yushaLocateY;
	int fieldData[6][6];//各マスのデータ
	int up;
	int left;
	int trout_Interval;

	int CommandFont, MassageFont;//フォント格納ハンドル
	int commandWindow, massageWindow, statusWindow;//画像格納ハンドル
	int commandWindowlocateX;
	int commandWindowlocateY;
	int commandCursol[2];
	int commandLayor;
	int B_FrameLocateX;
	int B_FrameLocateY;

	std::vector<Enemy> enemies;
	std::vector<int> enemyLocateX;
	std::vector<int> enemyLocateY;
	int enemyLockonX;
	int EnemyLockonY;

	std::shared_ptr<PartyControl> pc;

public:
	Battle_Stage();
	Battle_Stage(std::shared_ptr<PartyControl> pc_m);
	void B_Sort();
	void Draw_BattleStage();
	int DrawBattleCharacter();
	int PutYusha();
	int Yushamove(int yushaID);
	int Yushamove(int afterx, int aftery, int yushaID);
	int GetTroutState(int x, int y);
	int DrawBattleWindow(int scene);
	int Draw_Denger(int x,int y);
	int BackCommand();
	int getYushaLocateX(int yushaId);
	int getYushaLocateY(int yushaId);
	bool Check_can_attack(int x,int y,int yushaId);
	bool Check_enemy_attack(int x,int y,int enemyId);
	int EnemyTarget();
	int Draw_can_attack(int yushaId);
	int setB_FrameLocate(int mode);
	int setB_FrameLocate(int x, int y);
	int troutCursolup();
	int troutCursoldown();
	int troutCursolleft();
	int troutCursolright();
	int CheckTroutDistance(int yushaID,int TroutX,int TroutY);
	int CheckAttackRange(int yushaID,int TroutX,int TroutY);
	int DrawTroutCursol();
	int DrawCanMove(int yushaID);
	int Draw_Danger_Zone();
	int PutEnemy(int biome);
	bool Check_is_occupied(int x,int y);
	bool Check_is_enemy(int x, int y);
	bool Check_is_yusha(int x, int y);
	int Check_Enemy_Death();
	int Enemyturn();
	int Encount_Ani();
	int WaitCommand();
	int RunAsk();
	int SelectMove();
	int Selectattack();
	int Player_attack();
	int Player_Move();
	int Enemy_Attack();
	int Enemy_Move();
	int Result();
	int first();
	int next();
	int Use_Fireball();
	int Use_heal();
	bool Battle_Update();
};

