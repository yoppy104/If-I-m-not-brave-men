#include "DxLib.h"
#include <vector>
#include <time.h>
#include "Battle.h" 
#include "Player.h"
#include "Weapon.h"
#include "Magic.h"
#include "IDs.h"
#include "M_Functions.h"
#include <iostream>
#include "MapControl.h"
#include "Item.h"
#include <cstdlib>
#include <fstream>
#include "Battle_Stage.h"

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

	MapControl* mapc;
	
	//�摜�t�@�C���̓ǂݍ���
	int allen_image = LoadGraph("���m�A��������.png"); //�A�����̉摜

	int allen_image_dead = LoadGraph("���m�A����dead.png"); //�A�����̉摜

	// �����t�@�C���̓ǂݍ���
	int main = LoadSoundMem("00maintheme.wav"); //���C���e�[�}
	ChangeVolumeSoundMem(100, main);

	//Allen allen("�A����", 496 + 160 * 5, 136 + 160 * 5, 20, 10, 3, 6, 10, new WoodSword(), new NonHead(), new LeatherArm(), new LeatherChest(), new LeatherSheild(), allen_image, 10, allen_image_dead); // �A�����̍\���̒�`

	Player allen(ALLEN, 496 + 160 * 5, 136 + 160 * 5);//�G���[�ʒu

	return 0;//�ǂ܂�Ȃ�

	vector <Player*> players;
	//players.push_back(&allen);

	PartyControl* pc = new PartyControl(players, 0, 100);

	Battle_Stage* battle_stage = new Battle_Stage(pc);

	int mode = TITLE;

	//20 40
	mapc = new MapControl(1920, 1200, 20, 40, 1, players[0], pc);

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
			if (mapc->Update()) {
				mode = BATTLE_START;
			}
			break;
		case BATTLE_START:
			if (battle_stage->Battle_Update()) {
				mode = MAP_NORMAL;
			}
			break;
		}
		
	}

	InitSoundMem();
	DxLib_End(); // �c�w���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��
}
