#include "DxLib.h"
#include <vector>
#include <time.h>
#include "Battle.h" 
#include "Player.h"
#include "Allen.h"
#include "Craig.h"
#include "Imitia.h"
#include "Rain.h"
#include "Weapon.h"
#include "FireBall.h"
#include "IDs.h"
#include "M_Functions.h"
#include <iostream>
#include "Mathematic.h"
#include "MapControl.h"
#include "Items.h"
#include <cstdlib>
#include <fstream>

using namespace std;

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR pCmdLine, int CmdShow)
{
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
	SetGraphMode(1920, 1080, 32); // �E�B���h�E�T�C�Y���w��
	SetMainWindowText("NotBraveman"); // �E�B���h�E�^�C�g�����w��
	SetOutApplicationLogValidFlag(FALSE); // ���O���o�Ȃ��悤�ɐݒ�

	if (DxLib_Init() == -1) // DX���C�u�����̏�����
	{
		return -1; // �G���[��f������I��
	}

	SetFontSize(32); // �t�H���g�T�C�Y�̎w��

	ProcessMessage(); // ���荞�ݏ���������Ƃ��ɕK�{

	SRand(time(NULL));

	//createMap();

	MapControl mapc;
	
	//�摜�t�@�C���̓ǂݍ���
	int allen_image = LoadGraph("���m�A��������.png"); //�A�����̉摜
	int rain_image = LoadGraph("�����C������.png"); //���C���̉摜
	int craig_image = LoadGraph("���N���C�O����.png"); //�N���C�O�̉摜
	int imitia_image = LoadGraph("�|�C�~�e�B�A����.png"); //�C�~�e�B�A�̉摜

	int allen_image_dead = LoadGraph("���m�A����dead.png"); //�A�����̉摜
	int rain_image_dead = LoadGraph("�����C��dead.png"); //���C���̉摜
	int craig_image_dead = LoadGraph("���N���C�Odead.png"); //�N���C�O�̉摜
	int imitia_image_dead = LoadGraph("�|�C�~�e�B�Adead.png"); //�C�~�e�B�A�̉摜

	// �����t�@�C���̓ǂݍ���
	int main = LoadSoundMem("main(��)4_17.wav"); //���C���e�[�}

	Allen allen("�A����", 496 + 160 * 5, 136 + 160 * 5, 20, 6, 3, 6, 5, new WoodSword(), new NonHead(), new LeatherArm(), new LeatherChest(), new LeatherSheild(), allen_image, 10, allen_image_dead); // �A�����̍\���̒�`

	vector <Player*> players;
	players.push_back(&allen);

	PartyControl* pc = new PartyControl(players, 0, 100);

	int count_dead_players = 0;
	int count_dead_enemy = 0;

	int mode = TITLE;

	int click_stepframe = 30;

	mapc = MapControl(1920, 1200, 6, 5, 1, players[0], pc);

	int image_title = LoadGraph("�^�C�g��1920 1200.png");

	mode = TITLE;

	while (!CheckHitKey(KEY_INPUT_ESCAPE) && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		SetDrawScreen(DX_SCREEN_BACK);
		gpUpdateKey();
		switch (mode) {
		case TITLE:
			if (!CheckSoundMem(main)) {
				PlaySoundMem(main, DX_PLAYTYPE_LOOP, TRUE);
			}
			DrawGraph(0, 0, image_title, TRUE);
			if (CheckHitKeyAll()) {
				mode = MAP_NORMAL;
				StopSoundMem(main);
			}
			break;
		case MAP_NORMAL:
			if (mapc.Update()) {
				mode = BATTLE_START;
			}
			break;
		case BATTLE_START:
			DrawFormatString(100, 100, GetColor(255, 255, 255), "test encount");
			if (CheckHitKeyAll()) {
				mode = MAP_NORMAL;
			}
			break;
		}
		
	}

	InitSoundMem();
	DxLib_End(); // �c�w���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��
}