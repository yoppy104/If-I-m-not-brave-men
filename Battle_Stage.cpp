#include "Battle_Stage.h"
#include "Mathematic.h"


Battle_Stage::Battle_Stage()
{
	is_first_time = TRUE;
	troutCursol = FALSE;
	charaforcus = 0;
	enemyforcus = 0;
	scene = 0;
	number_of_character = 0;
	Anime_frame = 0;
	RunFail = false;
	Random = 0;
	Battle_End = false;

	dropEXP = 0;
	Dropgill = 0;

	B_Panel = LoadGraph("battlepanel.png");
	B_BG = LoadGraph("a.jpg");
	B_Cursol = LoadGraph("cursol.png");
	B_Frame = LoadGraph("battleframe.png");
	CanMoveTrout = LoadGraph("CanMoveTrout.png");
	Danger = LoadGraph("Danger.png");
	result = LoadGraph("Result.png");
	LoadDivGraph("Effects_Recovery.png", 8, 4, 2, 32, 32, heal);
	win = LoadSoundMem("win(test).wav");
	nomal = LoadSoundMem("nomal-battle.wav");
	sword = LoadSoundMem("刀剣・斬る07.mp3");
	punch = LoadSoundMem("手足・殴る、蹴る10.mp3");
	run_se = LoadSoundMem("足音・草原を走る.mp3");
	enemies_death = LoadSoundMem("パーン.mp3");

	srand(time(NULL));
	up = 136;
	left = 496;
	trout_Interval = 160;
	B_FrameLocateX = -1;
	B_FrameLocateY = -1;

	CommandFont = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	commandWindow = LoadGraph("command.png");
	statusWindow = LoadGraph("playerdata_gray.png");
	commandWindowlocateX = 100;
	commandWindowlocateY = 100;
	commandCursol[2] = {};
	commandLayor = 0;

	
	

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++) {
			fieldData[i][j] = 0;
			if (rand()%20==0)
			{
				fieldData[i][j] = 1;
			}
		}
	}

	
}

Battle_Stage::Battle_Stage(shared_ptr<PartyControl> pc)
{
	pc = pc;
	is_first_time = TRUE;
	troutCursol = FALSE;
	charaforcus = 0;
	enemyforcus = 0;
	scene = 0;
	number_of_character = 0;
	Anime_frame = 0;
	RunFail = false;
	Random = 0;
	Battle_End = false;

	dropEXP = 0;
	Dropgill = 0;

	B_Panel = LoadGraph("battlepanel.png");
	B_BG = LoadGraph("a.jpg");
	B_Cursol = LoadGraph("cursol.png");
	B_Frame = LoadGraph("battleframe.png");
	CanMoveTrout = LoadGraph("CanMoveTrout.png");
	Danger = LoadGraph("Danger.png");
	result = LoadGraph("Result.png");
	LoadDivGraph("Effects_Recovery.png", 8, 4, 2, 32, 32, heal);
	win = LoadSoundMem("win(test).wav");
	nomal = LoadSoundMem("nomal-battle.wav");
	sword = LoadSoundMem("刀剣・斬る07.mp3");
	punch = LoadSoundMem("手足・殴る、蹴る10.mp3");
	run_se = LoadSoundMem("足音・草原を走る.mp3");
	enemies_death = LoadSoundMem("パーン.mp3");

	srand(time(NULL));
	up = 136;
	left = 496;
	trout_Interval = 160;
	B_FrameLocateX = -1;
	B_FrameLocateY = -1;

	CommandFont = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	commandWindow = LoadGraph("command.png");
	statusWindow = LoadGraph("playerdata_gray.png");
	commandWindowlocateX = 100;
	commandWindowlocateY = 100;
	commandCursol[2] = {};
	commandLayor = 0;




	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++) {
			fieldData[i][j] = 0;
			if (rand() % 20 == 0)
			{
				fieldData[i][j] = 1;
			}
		}
	}


}

void Battle_Stage::B_Sort()
{
	sort.clear();
	is_enemy.clear();
	for (int i = 0; i < yushas.size(); i++)
	{
		sort.push_back(i);
		is_enemy.push_back(false);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		sort.push_back(i);
		is_enemy.push_back(true);
	}
	bool is_finish = false;
	while (!is_finish)
	{
		bool swaped = false;
		for (int i = 0; i < sort.size() - 1; i++)
		{
			if (!is_enemy[i] && !is_enemy[i+1] && yushas[sort[i]]->getDex() < yushas[sort[i+1]]->getDex()) //今、次ともにyushasの時
			{
				std::swap(sort[i], sort[i + 1]);
				std::swap(is_enemy[i], is_enemy[i + 1]);
				swaped = true;
			}
			if (is_enemy[i] && !is_enemy[i + 1] && enemies[sort[i]].GetDex() < yushas[sort[i + 1]]->getDex())//今enemies、次yushasの時
			{
				std::swap(sort[i], sort[i + 1]);
				std::swap(is_enemy[i], is_enemy[i + 1]);
				swaped = true;
			}
			if (!is_enemy[i] && is_enemy[i + 1] && yushas[sort[i]]->getDex() < enemies[sort[i + 1]].GetDex())//今yushas、次enemiesの時
			{
				std::swap(sort[i], sort[i + 1]);
				std::swap(is_enemy[i], is_enemy[i + 1]);
				swaped = true;
			}
			if (is_enemy[i] && is_enemy[i + 1] && enemies[sort[i]].GetDex() < enemies[sort[i + 1]].GetDex())//今、次ともにenemiesの時
			{
				std::swap(sort[i], sort[i + 1]);
				std::swap(is_enemy[i], is_enemy[i + 1]);
				swaped = true;
			}
		}
		if (!swaped)
		{
			is_finish = true;
		}
	}

}

void Battle_Stage::Draw_BattleStage()
{
	DrawGraph(0, 0, B_BG, FALSE);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++) {
			switch (fieldData[i][j])
			{
			case 0:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
				DrawGraph(left + trout_Interval * i, up + trout_Interval * j, B_Panel, FALSE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;
			case 1:
				break;
			default:
				break;
			}
				

		}
	}
	
}

int Battle_Stage::DrawBattleCharacter()
{
	for (int i = 0; i < yushas.size(); i++)
	{
		if (!yushas[i]->GetActive())
		{
			yushas[i]->DrawChar(left + trout_Interval * yushaLocateX[i], up + trout_Interval * yushaLocateY[i], 0);
		}
		
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i].GetActive())
		{
			enemies[i].DrawEnemy(left + trout_Interval * enemyLocateX[i], up + trout_Interval * enemyLocateY[i], 0);
		}
	}
	
	return 0;
}

int Battle_Stage::PutYusha()
{
	yushas.clear();
	yushaLocateX.clear();
	yushaLocateY.clear();
	int putX, putY;
	int i = 0;
	while ( i < pc->getNumMember())
	{
		putX = rand() % 6;
		putY = rand() % 6;
		if (Check_is_occupied(putX, putY) && fieldData[putX][putY] == 0)
		{
			yushas.push_back(pc->getMember(i));
			yushaLocateX.push_back(putX);
			yushaLocateY.push_back(putY);
			i++;
			number_of_character++;
		}
		
	}
	
	return 0;
}

int Battle_Stage::Yushamove(int yushaID)
{
	yushaLocateX[yushaID] = B_FrameLocateX;
	yushaLocateY[yushaID] = B_FrameLocateY;
	return 0;
}

int Battle_Stage::Yushamove(int afterx,int aftery,int yushaID)
{
	yushaLocateX[yushaID] = afterx;
	yushaLocateY[yushaID] = aftery;
	return 0;
}

int Battle_Stage::GetTroutState(int x, int y)
{
	return fieldData[x][y];
}

int Battle_Stage::DrawBattleWindow(int scene)
{
	
	DrawExtendGraph(commandWindowlocateX, commandWindowlocateY, commandWindowlocateX + 257, commandWindowlocateY + 513, commandWindow, FALSE);
	
	
	switch (scene)
	{
	case 1:
		DrawStringToHandle(150, 150, "たたかう", GetColor(150, 150, 150), CommandFont);
		DrawStringToHandle(150, 310, " 逃げる", GetColor(150, 150, 150), CommandFont);

		DrawLineAA(150, 195 + commandCursol[0] * 160, 310, 195 + commandCursol[0] * 160, GetColor(0, 0, 0), 4);
		switch (commandCursol[0])
		{
		case 0:
			DrawStringToHandle(150, 150, "たたかう", GetColor(0, 0, 0), CommandFont);
			break;
		case 1:
			DrawStringToHandle(150, 310, " 逃げる", GetColor(0, 0, 0), CommandFont);
			break;
		default:
			commandCursol[0] = 0;
			break;
		}
		break;
	case 2:
		DrawStringToHandle(150, 150, " 攻　撃", GetColor(150, 150, 150), CommandFont);
		DrawStringToHandle(150, 230, " 移　動", GetColor(150, 150, 150), CommandFont);
		DrawStringToHandle(150, 310, "アイテム", GetColor(150, 150, 150), CommandFont);
		DrawStringToHandle(150, 390, " 魔　術", GetColor(150, 150, 150), CommandFont);
		DrawStringToHandle(150, 470, " 防　御", GetColor(150, 150, 150), CommandFont);

		if (commandLayor == 0)
		{
			DrawLineAA(150, 195 + commandCursol[0] * 80, 310, 195 + commandCursol[0] * 80, GetColor(0, 0, 0), 4);
			switch (commandCursol[commandLayor])
			{
			case 0:
				DrawStringToHandle(150, 150, " 攻　撃", GetColor(0, 0, 0), CommandFont);
				break;
			case 1:
				DrawStringToHandle(150, 230, " 移　動", GetColor(0, 0, 0), CommandFont);
				break;
			case 2:
				DrawStringToHandle(150, 310, "アイテム", GetColor(0, 0, 0), CommandFont);
				break;
			case 3:
				DrawStringToHandle(150, 390, " 魔　術", GetColor(0, 0, 0), CommandFont);
				break;
			case 4:
				DrawStringToHandle(150, 470, " 防　御", GetColor(0, 0, 0), CommandFont);
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
	
	

	
	return 0;
}

int Battle_Stage::Draw_Denger(int x,int y){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawGraph(left + trout_Interval * x, up + trout_Interval * y, Danger, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	return 0;
}

int Battle_Stage::BackCommand()
{
	commandLayor=0;
	return 0;
}

int Battle_Stage::getYushaLocateX(int yushaId)
{
	return yushaLocateX[yushaId];
}

int Battle_Stage::getYushaLocateY(int yushaId)
{
	return yushaLocateY[yushaId];
}

bool Battle_Stage::Check_can_attack(int x,int y,int yushaId)
{
		if (Check_is_enemy(yushaLocateX[yushaId]+x,yushaLocateY[yushaId]+y))
		{
			return true;
		}
	return false;
}

bool Battle_Stage::Check_enemy_attack(int x, int y, int enemyId)
{
	
			if (Check_is_yusha(enemyLocateX[enemyId]+x,enemyLocateY[enemyId]+y))
			{
				enemyLockonX = enemyLocateX[enemyId] + x;
				EnemyLockonY = enemyLocateY[enemyId] + y;
				return true;
			}
		
	return false;
}

int Battle_Stage::EnemyTarget()
{
	int MAXhp = 10000;
	for (int i = 0; i < yushas.size(); i++)
	{
		if (yushas[i]->getHp()<=MAXhp && yushas[i]->getHp()>0)
		{
			MAXhp = yushas[i]->getHp();
			enemyLockonX = yushaLocateX[i];
			EnemyLockonY = yushaLocateY[i];
		}
	}

	return 0;
}

int Battle_Stage::Draw_can_attack(int yushaId)
{
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (Check_can_attack(i,j,yushaId))
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
				DrawGraph(left + trout_Interval * (yushaLocateX[yushaId]+i), up + trout_Interval * (yushaLocateY[yushaId]+j), CanMoveTrout, FALSE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			
		}
	}
	
	return 0;
}

int Battle_Stage::setB_FrameLocate(int mode)
{
	switch (mode)
	{
	case 0:
		B_FrameLocateX = yushaLocateX[sort[charaforcus]];
		B_FrameLocateY = yushaLocateY[sort[charaforcus]];
		break;
	case 1:
		
		break;
	default:
		break;
	}
	return 0;
}

int Battle_Stage::setB_FrameLocate(int x, int y)
{
	B_FrameLocateX = x;
	B_FrameLocateY = y;
	return 0;
}

int Battle_Stage::troutCursolup()
{
	switch (scene)
	{
	case 3:
		if (B_FrameLocateY != 0 && fieldData[B_FrameLocateX][B_FrameLocateY - 1] == 0 && CheckTroutDistance(sort[charaforcus], B_FrameLocateX, B_FrameLocateY - 1) != -1 && Check_is_occupied(B_FrameLocateX, B_FrameLocateY - 1))
		{
			B_FrameLocateY--;
		}
		break;
	case 4:
		if (B_FrameLocateY != 0 && CheckAttackRange(sort[charaforcus], B_FrameLocateX, B_FrameLocateY - 1) <= 1)
		{
			B_FrameLocateY--;
		}
		break;
	default:
		break;
	}
	
	
	return 0;
}

int Battle_Stage::troutCursoldown()
{
	switch (scene)
	{
	case 3:
		if (B_FrameLocateY != 5 && fieldData[B_FrameLocateX][B_FrameLocateY + 1] == 0 && CheckTroutDistance(sort[charaforcus], B_FrameLocateX, B_FrameLocateY + 1) != -1 && Check_is_occupied(B_FrameLocateX, B_FrameLocateY + 1))
		{
			B_FrameLocateY++;
		}
		break;
	case 4:
		if (B_FrameLocateY != 5 && CheckAttackRange(sort[charaforcus], B_FrameLocateX, B_FrameLocateY + 1) <= 1)
		{
			B_FrameLocateY++;
		}
		break;
	default:
		break;
	}
	
	return 0;
}

int Battle_Stage::troutCursolleft()
{
	switch (scene)
	{
	case 3:
		if (B_FrameLocateX != 0 && fieldData[B_FrameLocateX - 1][B_FrameLocateY] == 0 && CheckTroutDistance(sort[charaforcus], B_FrameLocateX - 1, B_FrameLocateY) != -1 && Check_is_occupied(B_FrameLocateX - 1, B_FrameLocateY))
		{
			B_FrameLocateX--;
		}
		break;
	case 4:
		if (B_FrameLocateX != 0 && CheckAttackRange(sort[charaforcus], B_FrameLocateX-1, B_FrameLocateY) <= 1)
		{
			B_FrameLocateX--;
		}
		break;
	default:
		break;
	}
	
	return 0;
}

int Battle_Stage::troutCursolright()
{
	switch (scene)
	{
	case 3:
		if (B_FrameLocateX != 5 && fieldData[B_FrameLocateX + 1][B_FrameLocateY] == 0 && CheckTroutDistance(sort[charaforcus], B_FrameLocateX + 1, B_FrameLocateY) != -1 && Check_is_occupied(B_FrameLocateX + 1, B_FrameLocateY))
		{
			B_FrameLocateX++;
		}
		break;
	case 4:
		if (B_FrameLocateX != 5 && CheckAttackRange(sort[charaforcus], B_FrameLocateX + 1, B_FrameLocateY) <= 1)
		{
			B_FrameLocateX++;
		}
		break;
	default:
		break;
	}
	
	return 0;
}

int Battle_Stage::CheckTroutDistance(int yushaID,int TroutX,int TroutY)
{
	return yushas[yushaID]->GetAGI() - (abs(TroutX-yushaLocateX[yushaID])+abs(TroutY - yushaLocateY[yushaID]));
}

int Battle_Stage::CheckAttackRange(int yushaID, int TroutX, int TroutY)
{
	int tmp = 0;
	tmp = abs(yushaLocateX[yushaID] - TroutX);
	if (tmp<abs(yushaLocateY[yushaID]-TroutY))
	{
		tmp = abs(yushaLocateY[yushaID] - TroutY);
	}
	return tmp;
}

int Battle_Stage::DrawTroutCursol()
{
	DrawGraph(left + trout_Interval * B_FrameLocateX, up + trout_Interval * B_FrameLocateY, B_Frame, FALSE);
	return 0;
}

int Battle_Stage::DrawCanMove(int yushaID)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++) {
			if (CheckTroutDistance(sort[charaforcus], i, j) >= 0 && fieldData[i][j] == 0 && Check_is_occupied(i,j)) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
				DrawGraph(left + trout_Interval * i, up + trout_Interval * j, CanMoveTrout, FALSE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
	return 0;
}

int Battle_Stage::Draw_Danger_Zone(){
	for ( int i = 0;  i < enemies.size(); i++)
	{
		
		switch (enemies[i].Getattacktype())
		{
		case 0:
			for (int j = -1; j < 2; j++)
			{

				for (int k = -1; k < 2; k++)
				{
					Draw_Denger(left + trout_Interval * (enemyLocateX[i] + j), up + trout_Interval * (enemyLocateY[i] + k));
				}
			}
			break;
		case 1:
			for (int j = -2; j < 3; j++)
			{

			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int Battle_Stage::PutEnemy(int biome)
{
	enemies.clear();
	enemyLocateX.clear();
	enemyLocateY.clear();
	Enemy USAGI("USAGI",600, 50, 10, 10, 10, "USAGI.png",0,0);
	int number = 2;
	int i = 0;
	int putX;
	int putY;
	while (i < number)
	{
		putX = rand() % 6;
		putY = rand() % 6;
		if (Check_is_occupied(putX,putY)&&fieldData[putX][putY]==0)
		{
			enemies.push_back(USAGI);
			enemyLocateX.push_back(putX);
			enemyLocateY.push_back(putY);
			i++;
			number_of_character++;
		}
		
	}
	return 0;
}

bool Battle_Stage::Check_is_occupied(int x,int y)
{
	for (int i = 0; i < yushas.size(); i++)
	{
		if (x==yushaLocateX[i]&&y==yushaLocateY[i])
		{
			return false;
		}
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		if (x == enemyLocateX[i] && y == enemyLocateY[i])
		{
			return false;
		}
	}
	return true;
}

bool Battle_Stage::Check_is_enemy(int x, int y)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (x == enemyLocateX[i] && y == enemyLocateY[i])
		{
			return true;
		}
	}
	return false;
}

bool Battle_Stage::Check_is_yusha(int x, int y)
{
	for (int i = 0; i < yushas.size(); i++)
	{
		if (x == yushaLocateX[i] && y == yushaLocateY[i] && yushas[i]->getHp()>0)
		{
			return true;
		}
	}
	return false;
}

int Battle_Stage::Check_Enemy_Death()
{
	
	auto itr = enemies.begin();
	auto itr2 = enemyLocateX.begin();
	auto itr3 = enemyLocateY.begin();
	
	while (itr != enemies.end())
	{
		
		if (itr->GetHp()<=0)
		{
			dropEXP += itr->GetEXP();
			Dropgill += itr->GetGill();
			PlaySoundMem(enemies_death, DX_PLAYTYPE_BACK);
			itr = enemies.erase(itr);
			itr2 = enemyLocateX.erase(itr2);
			itr3 = enemyLocateY.erase(itr3);
		}
		else
		{
			itr++;
			itr2++;
			itr3++;
		}
	}


	return 0;
}

int Battle_Stage::Enemyturn()
{
	bool attack=false;
	switch (enemies[sort[charaforcus]].Getattacktype())
	{
	case 0:
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (Check_enemy_attack(i, j, sort[charaforcus]))
				{
					scene = 9;
					attack = true;
				}

			}
		}
		break;
	case 1:
		for (int i = -2; i < 3; i++)
		{
			if (Check_enemy_attack(i, 0, sort[charaforcus]))
			{
				scene = 9;
				attack = true;
			}
		}
		for (int i = -2; i < 3; i++)
		{
			if (Check_enemy_attack(0, i, sort[charaforcus]))
			{
				scene = 9;
				attack = true;
			}
		}
		break;
	case 2:
		for (int i = -1; i < 2; i += 2)
		{
			for (int j = -1; j < 2; j += 2)
			{
				if (Check_enemy_attack(i, j, sort[charaforcus]))
				{
					scene = 9;
					attack = true;
				}

			}
		}
		for (int i = -2; i < 3; i+=4)
		{

			for (int j = -2; j < 3; j+=4)
			{
				if (Check_enemy_attack(i, j, sort[charaforcus]))
				{
					scene = 9;
					attack = true;
				}
			}

		}
		break;
	default:
		break;
	}
	
	if (!attack)
	{
		scene = 10;
	}
	
	return 0;
}

int Battle_Stage::Encount_Ani()
{
	scene = 1;
	return 0;
}

int Battle_Stage::WaitCommand()
{

	if (Button(KEY_INPUT_DOWN) == 1)
	{
		commandCursol[commandLayor]++;
	}
	if (Button(KEY_INPUT_UP) == 1)
	{
		commandCursol[commandLayor]--;
	}
	if (Button(KEY_INPUT_SPACE) == 1 && commandLayor < 1)
	{
		commandLayor++;
	}
	if (Button(KEY_INPUT_B) == 1 && commandLayor != 0)
	{
		commandLayor--;
	}
	
	switch (commandCursol[0])
	{
	case 0:
		if (Button(KEY_INPUT_SPACE) == 1)
		{
			commandLayor = 0;
			setB_FrameLocate(0);
			scene = 4;
		}
		break;
	case 1:
		if (Button(KEY_INPUT_SPACE) == 1)
		{
			commandLayor = 0;
			setB_FrameLocate(0);
			scene = 3;
		}
		break;
	case 3:
		if (Button(KEY_INPUT_SPACE) == 1)
		{
			commandLayor = 1;
		}
		break;
	case 4:
		if (Button(KEY_INPUT_SPACE) == 1)
		{
			commandLayor = 0;
			yushas[sort[charaforcus]]->ActBlock();
			yushas[sort[charaforcus]]->Activate();
			next();
		}
		break;

	default:
		break;
	}
	switch (commandLayor)
	{
	
	
	case 1:
		switch (commandCursol[0]){
		case 2:
			DrawExtendGraph(commandWindowlocateX + 50, commandWindowlocateY + 50, commandWindowlocateX + 307, commandWindowlocateY + 563, commandWindow, FALSE);
			break;
		case 3:
			DrawExtendGraph(commandWindowlocateX + 50, commandWindowlocateY + 50, commandWindowlocateX + 307, commandWindowlocateY + 563, commandWindow, FALSE);
			DrawFormatStringToHandle(200, 200, GetColor(150, 150, 150), CommandFont, "ファイア\n ボール");
			DrawStringToHandle(200, 300, " ヒール", GetColor(150, 150, 150), CommandFont);
			commandCursol[1] %= 2;
			if (commandCursol[1]<0)
			{
				commandCursol[1] = 1;
			}
			switch (commandCursol[1])
			{
			case 0:
				DrawFormatStringToHandle(200, 200, GetColor(0, 0, 0), CommandFont, "ファイア\n ボール");
				DrawLineAA(200, 245 + commandCursol[1] * 100, 360, 245 + commandCursol[1] * 100, GetColor(0, 0, 0), 4);
				DrawLineAA(230, 285 + commandCursol[1] * 100, 330, 285 + commandCursol[1] * 100, GetColor(0, 0, 0), 4);
				if (Button(KEY_INPUT_SPACE) >= 10)
				{
					yushas[sort[charaforcus]]->SetAniframe(0);
					commandCursol[1] = 0;
					scene = 7;
				}
				break;
			case 1:
				DrawLineAA(200, 245 + commandCursol[1] * 100, 360, 245 + commandCursol[1] * 100, GetColor(0, 0, 0), 4);
				DrawStringToHandle(200, 300, " ヒール", GetColor(0, 0, 0), CommandFont);
				if (Button(KEY_INPUT_SPACE) >= 10)
				{
					yushas[sort[charaforcus]]->SetAniframe(0);
					commandCursol[1] = 0;
					scene = 11;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
		
	
	
	
	
		
	
	
	
	yushas[sort[charaforcus]]->DrawChar(left + trout_Interval * yushaLocateX[sort[charaforcus]], up + trout_Interval * yushaLocateY[sort[charaforcus]], 0);
	commandCursol[0] %= 5;
	if (commandCursol[0] < 0)
	{
		commandCursol[0] = 4;
	}
	return 0;
}

int Battle_Stage::RunAsk()
{
	RunFail = false;
	if (Button(KEY_INPUT_DOWN) == 1)
	{
		commandCursol[0]++;
	}
	if (Button(KEY_INPUT_UP) == 1)
	{
		commandCursol[0]--;
	}
	commandCursol[0] %= 2;
	if (commandCursol[0] < 0)
	{
		commandCursol[0] = 1;
	}
	if (Button(KEY_INPUT_SPACE) == 1 && commandCursol[0] == 0)
	{
		next();
		commandCursol[0] = 0;
	}
	if (Button(KEY_INPUT_SPACE) == 1 && commandCursol[0] == 1)
	{
		if (rand() % 4 == 0)
		{
			scene = 8;
		}
		else
		{
			RunFail = true;
		}
		next();
	}
	return 0;
}

int Battle_Stage::SelectMove()
{
	yushas[sort[charaforcus]]->DrawChar(left + trout_Interval * yushaLocateX[sort[charaforcus]], up + trout_Interval * yushaLocateY[sort[charaforcus]], 0);
	troutCursol = true;
	if (Button(KEY_INPUT_DOWN) == 1)
	{
		troutCursoldown();
	}
	if (Button(KEY_INPUT_UP) == 1)
	{
		troutCursolup();
	}
	if (Button(KEY_INPUT_LEFT) == 1)
	{
		troutCursolleft();
	}
	if (Button(KEY_INPUT_RIGHT) == 1)
	{
		troutCursolright();
	}
	if (Button(KEY_INPUT_B) == 1)
	{
		yushas[sort[charaforcus]]->SetAniframe(0);
		troutCursol = false;
		scene = 2;
	}
	if (Button(KEY_INPUT_SPACE)==1)
	{
		troutCursol = false;
		scene = 6;

	}
	return 0;
}

int Battle_Stage::Selectattack()
{
	yushas[sort[charaforcus]]->DrawChar(left + trout_Interval * yushaLocateX[sort[charaforcus]], up + trout_Interval * yushaLocateY[sort[charaforcus]], 0);
	troutCursol = true;
	if (Button(KEY_INPUT_DOWN) == 1)
	{
		troutCursoldown();
	}
	if (Button(KEY_INPUT_UP) == 1)
	{
		troutCursolup();
	}
	if (Button(KEY_INPUT_LEFT) == 1)
	{
		troutCursolleft();
	}
	if (Button(KEY_INPUT_RIGHT) == 1)
	{
		troutCursolright();
	}
	if (Button(KEY_INPUT_SPACE) == 1 && Check_is_enemy(B_FrameLocateX,B_FrameLocateY))
	{
		yushas[sort[charaforcus]]->SetAniframe(0);
		troutCursol = false;
		scene = 5;
	}
	if (Button(KEY_INPUT_B) == 1)
	{
		troutCursol = false;
		scene = 2;
	}
	return 0;
}

int Battle_Stage::Player_attack()
{
	yushas[sort[charaforcus]]->DrawChar(left + B_FrameLocateX * trout_Interval + 120, up + B_FrameLocateY * trout_Interval, 1);
	Anime_frame++;
	if (Anime_frame==30)
	{
		PlaySoundMem(sword, DX_PLAYTYPE_BACK);
	}
	if (Anime_frame>60)
	{
		for (int i = 0; i < enemies.size(); ++i)
		{
			if (enemyLocateX[i] == B_FrameLocateX && enemyLocateY[i] == B_FrameLocateY)
			{
				enemies[i].Damage(damage(yushas[sort[charaforcus]]->getAttack(), enemies[i].GetDiffence(), 0.5));

			}
		}

		yushas[sort[charaforcus]]->Activate();
		next();
	}
	
	return 0;
}

int Battle_Stage::Player_Move()
{
	double dx = (B_FrameLocateX-yushaLocateX[sort[charaforcus]])*trout_Interval / 20;
	double dy = (B_FrameLocateY-yushaLocateY[sort[charaforcus]])*trout_Interval / 20;
	double x = left + trout_Interval * yushaLocateX[sort[charaforcus]] + dx *Anime_frame;
	double y = up + trout_Interval * yushaLocateY[sort[charaforcus]] + dy * Anime_frame;
	if (CheckSoundMem(run_se) == 0)
	{
		PlaySoundMem(run_se, DX_PLAYTYPE_BACK);
	}
	yushas[sort[charaforcus]]->DrawChar(x, y, 3);

	Anime_frame++;
	if (Anime_frame>20)
	{
		StopSoundMem(run_se);
		Yushamove(sort[charaforcus]);
		yushas[sort[charaforcus]]->Activate();
		next();
	}
	
	return 0;
}

int Battle_Stage::Enemy_Attack()
{
	enemies[sort[charaforcus]].DrawEnemy(left + trout_Interval * enemyLockonX + 120, up + EnemyLockonY * trout_Interval , 0);
	Anime_frame++;
	if (Anime_frame==20)
	{
		PlaySoundMem(punch, DX_PLAYTYPE_BACK, true);
	}
	if (Anime_frame>40)
	{
		for (int i = 0; i < yushas.size(); ++i)
		{
			if (yushaLocateX[i] == enemyLockonX && yushaLocateY[i] == EnemyLockonY)
			{
				yushas[i]->Damage(damage(enemies[sort[charaforcus]].GetAttack(), yushas[i]->getDiffence(), 0.5));

			}
		}
		enemies[sort[charaforcus]].Activate();
		next();
	}
	return 0;
}

int Battle_Stage::Enemy_Move()
{
	EnemyTarget();
	
	switch (enemies[sort[charaforcus]].Getmovetype()){
	case 0:
		if (enemyLocateX[sort[charaforcus]]<enemyLockonX &&
			fieldData[enemyLocateX[sort[charaforcus]] + 1][enemyLocateY[sort[charaforcus]]] == 0 &&
			Check_is_occupied(enemyLocateX[sort[charaforcus]] + 1, enemyLocateY[sort[charaforcus]]))
		{
			if (CheckSoundMem(run_se)==0)
			{
				PlaySoundMem(run_se, DX_PLAYTYPE_BACK);
			}
			double dx = trout_Interval / 20;
			double x = left + trout_Interval * enemyLocateX[sort[charaforcus]] + dx * Anime_frame;
			Anime_frame++;
			enemies[sort[charaforcus]].DrawEnemy(x, up + trout_Interval * enemyLocateY[sort[charaforcus]], 0);
			if (Anime_frame>20)
			{
				StopSoundMem(run_se);
				enemyLocateX[sort[charaforcus]]++;
				enemies[sort[charaforcus]].Activate();
				next();
			}
			return 0;
		}
		else if (enemyLocateX[sort[charaforcus]] > enemyLockonX &&
			fieldData[enemyLocateX[sort[charaforcus]] - 1][enemyLocateY[sort[charaforcus]]] == 0 &&
			Check_is_occupied(enemyLocateX[sort[charaforcus]] - 1, enemyLocateY[sort[charaforcus]]))
		{
			if (CheckSoundMem(run_se) == 0)
			{
				PlaySoundMem(run_se, DX_PLAYTYPE_BACK);
			}
			double dx = -1 * trout_Interval / 20;
			double x = left + trout_Interval * enemyLocateX[sort[charaforcus]] + dx * Anime_frame;
			Anime_frame++;
			enemies[sort[charaforcus]].DrawEnemy(x, up + trout_Interval * enemyLocateY[sort[charaforcus]], 0);
			if (Anime_frame>20)
			{
				StopSoundMem(run_se);
				enemyLocateX[sort[charaforcus]]--;
				enemies[sort[charaforcus]].Activate();
				next();
			}
			return 0;
		}
		else if (enemyLocateY[sort[charaforcus]] < EnemyLockonY &&
			fieldData[enemyLocateX[sort[charaforcus]]][enemyLocateY[sort[charaforcus]] + 1] == 0 &&
			Check_is_occupied(enemyLocateX[sort[charaforcus]], enemyLocateY[sort[charaforcus]] + 1))
		{
			if (CheckSoundMem(run_se) == 0)
			{
				PlaySoundMem(run_se, DX_PLAYTYPE_BACK);
			}
			double dy = trout_Interval / 20;
			double y = up + trout_Interval * enemyLocateY[sort[charaforcus]] + dy * Anime_frame;
			Anime_frame++;
			enemies[sort[charaforcus]].DrawEnemy(left + trout_Interval * enemyLocateX[sort[charaforcus]], y, 0);
			if (Anime_frame > 20)
			{
				StopSoundMem(run_se);
				enemyLocateY[sort[charaforcus]]++;
				enemies[sort[charaforcus]].Activate();
				next();
			}
			return 0;
		}
		else if (enemyLocateY[sort[charaforcus]] > EnemyLockonY &&
			fieldData[enemyLocateX[sort[charaforcus]]][enemyLocateY[sort[charaforcus]] - 1] == 0 &&
			Check_is_occupied(enemyLocateX[sort[charaforcus]], enemyLocateY[sort[charaforcus]] - 1))
		{
			if (CheckSoundMem(run_se) == 0)
			{
				PlaySoundMem(run_se, DX_PLAYTYPE_BACK);
			}
			double dy = -1 * trout_Interval / 20;
			double y = up + trout_Interval * enemyLocateY[sort[charaforcus]] + dy * Anime_frame;
			Anime_frame++;
			enemies[sort[charaforcus]].DrawEnemy(left + trout_Interval * enemyLocateX[sort[charaforcus]], y, 0);
			if (Anime_frame > 20)
			{
				StopSoundMem(run_se);
				enemyLocateY[sort[charaforcus]]--;
				enemies[sort[charaforcus]].Activate();
				next();
			}
			return 0;
		}
		else
		{
			enemies[sort[charaforcus]].DrawEnemy(left + trout_Interval * enemyLocateX[sort[charaforcus]], up + trout_Interval * enemyLocateY[sort[charaforcus]], 0);
			enemies[sort[charaforcus]].Activate();
			next();
		}

		break;
	case 1:
		switch (Random)
		{
		case 0:
			if (fieldData[enemyLocateX[sort[charaforcus]] + 1][enemyLocateY[sort[charaforcus]]] == 0 &&
				Check_is_occupied(enemyLocateX[sort[charaforcus]] + 1, enemyLocateY[sort[charaforcus]]) &&
				enemyLocateX[sort[charaforcus]]!=5)
			{
				double dx = trout_Interval / 20;
				double x = left + trout_Interval * enemyLocateX[sort[charaforcus]] + dx * Anime_frame;
				Anime_frame++;
				enemies[sort[charaforcus]].DrawEnemy(x, up + trout_Interval * enemyLocateY[sort[charaforcus]], 0);
				if (Anime_frame>20)
				{
					enemyLocateX[sort[charaforcus]]++;
					enemies[sort[charaforcus]].Activate();
					next();
				}
			}
			break;
		case 1:
			if (fieldData[enemyLocateX[sort[charaforcus]] - 1][enemyLocateY[sort[charaforcus]]] == 0 &&
				Check_is_occupied(enemyLocateX[sort[charaforcus]] - 1, enemyLocateY[sort[charaforcus]]) &&
				enemyLocateX[sort[charaforcus]] != 0)
			{
				double dx = -1 * trout_Interval / 20;
				double x = left + trout_Interval * enemyLocateX[sort[charaforcus]] + dx * Anime_frame;
				Anime_frame++;
				enemies[sort[charaforcus]].DrawEnemy(x, up + trout_Interval * enemyLocateY[sort[charaforcus]], 0);
				if (Anime_frame>20)
				{
					enemyLocateX[sort[charaforcus]]--;
					enemies[sort[charaforcus]].Activate();
					next();
				}
			}
			break;
		case 2:
			if (fieldData[enemyLocateX[sort[charaforcus]]][enemyLocateY[sort[charaforcus]] + 1] == 0 &&
				Check_is_occupied(enemyLocateX[sort[charaforcus]], enemyLocateY[sort[charaforcus]] + 1) &&
				enemyLocateY[sort[charaforcus]] != 5)
			{
				double dy = trout_Interval / 20;
				double y = up + trout_Interval * enemyLocateY[sort[charaforcus]] + dy * Anime_frame;
				Anime_frame++;
				enemies[sort[charaforcus]].DrawEnemy(left + trout_Interval * enemyLocateX[sort[charaforcus]], y, 0);
				if (Anime_frame > 20)
				{
					enemyLocateY[sort[charaforcus]]++;
					enemies[sort[charaforcus]].Activate();
					next();
				}
			}
			break;
		case 3:
			if (fieldData[enemyLocateX[sort[charaforcus]]][enemyLocateY[sort[charaforcus]] - 1] == 0 &&
				Check_is_occupied(enemyLocateX[sort[charaforcus]], enemyLocateY[sort[charaforcus]] - 1) &&
				enemyLocateY[sort[charaforcus]] != 0)
			{
				double dy = -1 * trout_Interval / 20;
				double y = up + trout_Interval * enemyLocateY[sort[charaforcus]] + dy * Anime_frame;
				Anime_frame++;
				enemies[sort[charaforcus]].DrawEnemy(left + trout_Interval * enemyLocateX[sort[charaforcus]], y, 0);
				if (Anime_frame > 20)
				{
					enemyLocateY[sort[charaforcus]]--;
					enemies[sort[charaforcus]].Activate();
					next();
				}
			}
			break;
		case 4://x+y+
			if (fieldData[enemyLocateX[sort[charaforcus]] + 1][enemyLocateY[sort[charaforcus]] + 1] == 0 &&
				Check_is_occupied(enemyLocateX[sort[charaforcus]] + 1, enemyLocateY[sort[charaforcus]] + 1) &&
				enemyLocateX[sort[charaforcus]] != 5 && enemyLocateY[sort[charaforcus]] != 5)
			{
				double dx = trout_Interval / 20;
				double x = left + trout_Interval * enemyLocateX[sort[charaforcus]] + dx * Anime_frame;
				double dy = trout_Interval / 20;
				double y = up + trout_Interval * enemyLocateY[sort[charaforcus]] + dy * Anime_frame;
				Anime_frame++;
				enemies[sort[charaforcus]].DrawEnemy(x, y, 0);
				if (Anime_frame>20)
				{
					enemyLocateX[sort[charaforcus]]++;
					enemyLocateY[sort[charaforcus]]++;
					enemies[sort[charaforcus]].Activate();
					next();
				}
			}
			break;
		case 5://x+y-
			if (fieldData[enemyLocateX[sort[charaforcus]] + 1][enemyLocateY[sort[charaforcus]] - 1] == 0 &&
				Check_is_occupied(enemyLocateX[sort[charaforcus]] + 1, enemyLocateY[sort[charaforcus]] - 1) &&
				enemyLocateX[sort[charaforcus]] != 5 && enemyLocateY[sort[charaforcus]] != 0)
			{
				double dx = trout_Interval / 20;
				double x = left + trout_Interval * enemyLocateX[sort[charaforcus]] + dx * Anime_frame;
				double dy = trout_Interval / 20;
				double y = -1 * up + trout_Interval * enemyLocateY[sort[charaforcus]] + dy * Anime_frame;
				Anime_frame++;
				enemies[sort[charaforcus]].DrawEnemy(x, y, 0);
				if (Anime_frame>20)
				{
					enemyLocateX[sort[charaforcus]]++;
					enemyLocateY[sort[charaforcus]]--;
					enemies[sort[charaforcus]].Activate();
					next();
				}
			}
			break;
		case 6://x-y+
			if (fieldData[enemyLocateX[sort[charaforcus]] - 1][enemyLocateY[sort[charaforcus]] + 1] == 0 &&
				Check_is_occupied(enemyLocateX[sort[charaforcus]] - 1, enemyLocateY[sort[charaforcus]] + 1) &&
				enemyLocateX[sort[charaforcus]] != 0 && enemyLocateY[sort[charaforcus]] != 5)
			{
				double dx = -1 * trout_Interval / 20;
				double x = left + trout_Interval * enemyLocateX[sort[charaforcus]] + dx * Anime_frame;
				double dy = trout_Interval / 20;
				double y = up + trout_Interval * enemyLocateY[sort[charaforcus]] + dy * Anime_frame;
				Anime_frame++;
				enemies[sort[charaforcus]].DrawEnemy(x, y, 0);
				if (Anime_frame>20)
				{
					enemyLocateX[sort[charaforcus]]--;
					enemyLocateY[sort[charaforcus]]++;
					enemies[sort[charaforcus]].Activate();
					next();
				}
			}
			break;
		case 7://x-y-
			if (fieldData[enemyLocateX[sort[charaforcus]] - 1][enemyLocateY[sort[charaforcus]] - 1] == 0 &&
				Check_is_occupied(enemyLocateX[sort[charaforcus]] - 1, enemyLocateY[sort[charaforcus]] - 1) &&
				enemyLocateX[sort[charaforcus]] != 0 && enemyLocateY[sort[charaforcus]] != 0)
			{
				double dx = -1 * trout_Interval / 20;
				double x = left + trout_Interval * enemyLocateX[sort[charaforcus]] + dx * Anime_frame;
				double dy = -1 * trout_Interval / 20;
				double y = up + trout_Interval * enemyLocateY[sort[charaforcus]] + dy * Anime_frame;
				Anime_frame++;
				enemies[sort[charaforcus]].DrawEnemy(x, y, 0);
				if (Anime_frame>20)
				{
					enemyLocateX[sort[charaforcus]]--;
					enemyLocateY[sort[charaforcus]]--;
					enemies[sort[charaforcus]].Activate();
					next();
				}
			}
			break;
		default:
			enemies[sort[charaforcus]].Activate();
			next();
			break;
		}
		break;
	case 2:
		enemies[sort[charaforcus]].DrawEnemy(left + trout_Interval * enemyLocateX[sort[charaforcus]], up + trout_Interval * enemyLocateY[sort[charaforcus]],0);
		enemies[sort[charaforcus]].Activate();
		next();
		break;
	default:
		break;
	}
	return 0;
}

int Battle_Stage::first()
{
	Anime_frame = 0;
	Check_Enemy_Death();
	B_Sort();
	scene = 0;
	charaforcus = -1;
	return 0;
}

int Battle_Stage::next()
{
	charaforcus++;
	if (charaforcus==sort.size())
	{
		commandCursol[0] = 0;
		scene = 1;
		charaforcus = -1;
		return 1;
	}
	Anime_frame = 0;
	Check_Enemy_Death();
	if (enemies.empty()) {
		scene = 8;
		return 2;
	}
	B_Sort();
	if (is_enemy[charaforcus]) {
		enemies[sort[charaforcus]].Activate();
		Enemyturn();
	}
	if (!is_enemy[charaforcus])
	{
		yushas[sort[charaforcus]]->ReleaseBlock();
		yushas[sort[charaforcus]]->Activate();
		scene = 2;
	}
	
	return 0;
}

int Battle_Stage::Result(){
	if (CheckSoundMem(win)==0){
		StopSoundMem(nomal);
		PlaySoundMem(win, DX_PLAYTYPE_LOOP, TRUE);
		pc->getMember(0)->sendEXp(dropEXP);
	}
	DrawGraph(767, 215, result, TRUE);
	DrawStringToHandle(830, 250, "RESULT", GetColor(0, 0, 0), CommandFont);
	DrawLineAA(830, 290, 950, 290, GetColor(0, 0, 0), 2);
	DrawStringToHandle(830, 360, "取得したギル", GetColor(0, 0, 0), CommandFont);
	DrawFormatStringToHandle(830, 410, GetColor(0, 0, 0), CommandFont, "%d", Dropgill);
	DrawStringToHandle(830, 490, "取得した経験値", GetColor(0, 0, 0), CommandFont);
	DrawFormatStringToHandle(830, 540, GetColor(0, 0, 0), CommandFont, "%d", dropEXP);
	DrawStringToHandle(830, 600, "Allen", GetColor(0, 0, 0), CommandFont);
	DrawStringToHandle(830, 645, "LV.", GetColor(0, 0, 0), CommandFont);
	DrawFormatStringToHandle(890, 645, GetColor(0, 0, 0), CommandFont, "%d → %d", yushas[0]->GetLV(),pc->getMember(0)->GetLV());

	if (Button(KEY_INPUT_SPACE)>=1)
	{
		scene = 30;
	}


	return 0;
}

int Battle_Stage::Use_Fireball(){
	troutCursol = true;
	yushas[sort[charaforcus]]->DrawChar(left + trout_Interval * yushaLocateX[sort[charaforcus]], up + trout_Interval * yushaLocateY[sort[charaforcus]],0);
	setB_FrameLocate(enemyLocateX[commandCursol[1]], enemyLocateY[commandCursol[1]]);
	if (Button(KEY_INPUT_DOWN) == 1 && commandCursol[1]+1<enemies.size())
	{
		commandCursol[1]++;
	}
	if (Button(KEY_INPUT_UP) == 1 && commandCursol[1] - 1 >= 0)
	{
		commandCursol[1]--;
	}
	if (Button(KEY_INPUT_SPACE) == 1)
	{
		enemies[commandCursol[1]].Damage(yushas[sort[charaforcus]]->getMagicPower() + 5);
		yushas[sort[charaforcus]]->Activate();
		next();
		commandLayor = 0;
		troutCursol = false;
	}
	if (Button(KEY_INPUT_B) == 1)
	{
		commandLayor = 0;
		troutCursol = false;
	}
	return 0;
}

int  Battle_Stage::Use_heal(){
	
	yushas[sort[charaforcus]]->DrawChar(left + trout_Interval * yushaLocateX[sort[charaforcus]], up + trout_Interval * yushaLocateY[sort[charaforcus]],0);
	DrawExtendGraph(left + trout_Interval * yushaLocateX[sort[charaforcus]], up + trout_Interval * yushaLocateY[sort[charaforcus]], left + trout_Interval * yushaLocateX[sort[charaforcus]] + 128, up + trout_Interval * yushaLocateY[sort[charaforcus]] +128,heal[Anime_frame/10],true);
	Anime_frame++;
	if (Anime_frame > 80)
	{
		yushas[sort[charaforcus]]->Damage(-1 * yushas[sort[charaforcus]]->getMagicPower());
		yushas[sort[charaforcus]]->Activate();
		next();
		commandLayor = 0;
	}
	
	return 0;
}

bool Battle_Stage::Battle_Update()
{
	pc->getMember(0)->DrawSta(1500, 50);

	if (is_first_time == true)
	{
		PlaySoundMem(nomal, DX_PLAYTYPE_LOOP);
		PutYusha();
		PutEnemy(0);
		is_first_time = false;
		first();
	}
	
	Draw_BattleStage();
	DrawBattleWindow(scene);
	if (Button(KEY_INPUT_LSHIFT)>0)
	{
		Draw_Danger_Zone();
	}
	if (troutCursol == TRUE)
	{
		switch (scene)
		{
		case 3:
			DrawCanMove(sort[charaforcus]);
			break;
		case 4:
			Draw_can_attack(sort[charaforcus]);
			break;
		default:
			break;
		}
		DrawTroutCursol();
	}
	DrawBattleCharacter();
	switch (scene)
	{
	case 0:// エンカウント時のアニメーション表示
		Encount_Ani();
		break;
	case 1:// 逃げるか逃げないか選ばせる
		RunAsk();
		break;
	case 2:// コマンド選択
		WaitCommand();
		break;
	case 3:// 自キャラ移動先選択
		SelectMove();
		break;
	case 4:// 自キャラ攻撃先選択
		Selectattack();
		break;
	case 5:// キャラ攻撃シーン
		Player_attack();
		break;
	case 6:// キャラ移動シーン
		Player_Move();
		break;
	case 7:// アイテムorスキル使用シーン
		Use_Fireball();
		break;
	case 8:// バトル終了
		Result();
		break;
	case 9:
		Enemy_Attack();
		break;
	case 10:
		Enemy_Move();
		break;
	case 11:
		Use_heal();
		break;
	default:
		is_first_time = TRUE;
		troutCursol = FALSE;
		charaforcus = 0;
		enemyforcus = 0;
		scene = 0;
		number_of_character = 0;
		Anime_frame = 0;
		RunFail = false;
		Random = 0;
		Battle_End = false;
		pc->addNumCoin(Dropgill);

		dropEXP = 0;
		Dropgill = 0;

		return true;
		break;
	}
	
	return false;
}