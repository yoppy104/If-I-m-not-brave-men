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
	ChangeWindowMode(true); // �E�C���h�E���[�h�ɕύX
	SetGraphMode(1920, 1200, 32); // �E�B���h�E�T�C�Y���w��
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


	WoodSword* iron_sword(); // �����̃N���X
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
	int title_image = LoadGraph("�^�C�g��1920 1200.png");

	// �����t�@�C���̓ǂݍ���
	int battle_bgm = LoadSoundMem("nomal-battle.wav"); //�o�g��BGM
	int button_se = LoadSoundMem("�s�R�I.mp3"); //�{�^�����쉹
	int walk_se = LoadSoundMem("�����E�����𑖂�.mp3"); //���s��
	int move_slime_se = LoadSoundMem("�h���h����������.mp3"); //�X���C���̈ړ���
	int attack_slime_se = LoadSoundMem("�葫�E����A�R��10.mp3"); //�X���C���̍U����
	int sound_cancel = LoadSoundMem("�{�^����44.mp3"); //�L�����Z����
	int sound_define = LoadSoundMem("�{�^����14.mp3"); //���艹
	int main = LoadSoundMem("main(��)4_17.wav"); //���C���e�[�}


	Allen allen("�A����", 496 + 160 * 5, 136 + 160 * 5, 20, 6, 3, 6, 5, WoodSword(), allen_image, 10, allen_image_dead); // �A�����̍\���̒�`
	fstream file;
	file.open("allendata.dat", ios::binary | ios::in);
	file.read((char*)&allen, sizeof(allen));
	file.close();
	/*
	Rain rain("���C��", 496 + 160 * 4, 136 + 160 * 5, 15, 4, 4, 10, 3, WoodSword(), rain_image, rain_image_dead); // ���C���̍\���̒�`
	Craig craig("�N���C�O", 496 + 160 * 0, 136 + 160 * 5, 25, 10, 7, 0, 2, WoodSword(), craig_image, craig_image_dead); // �N���C�O�̍\���̒�`
	Imitia imitia("�C�~�e�B�A", 496 + 160 * 1, 136 + 160 * 5, 20, 6, 8, 7, 6, WoodSword(), imitia_image, imitia_image_dead); // �C�~�e�B�A�̍\���̒�`
	*/
	vector <Player*> players = { &allen };
	/*
	for (int i = 1; i < players.size(); i++) {
		int j = i;
		while (j > 0 && players[j]->getDex() > players[j - 1]->getDex()) {
			Player* t = players[j - 1];
			players[j - 1] = players[j];
			players[j] = t;
		}
	}
	*/
	PartyControl pc(players, 0, 100);
	/*
	fstream file;
	file.open("savedata.dat", ios::binary | ios::in);
	file.read((char*)&pc, sizeof(pc));
	file.close();
	*/
	int enemy_image = LoadGraph("�X���C��.png"); // �G�̉摜
	int enemy_image_dead = LoadGraph("�X���C��dead.png");

	//�X�e�[�W�̃f�[�^�l
	stagedata stage = 0b1111111111111111111111111111111111111;

	int battlemap_left = 496; // �}�b�v�̍��̍��W
	int battlemap_top = 136; // �}�b�v�̏�̍��W

	int count_dead_players = 0;
	int count_dead_enemy = 0;

	int mode = TITLE;
	int drawmode = 0;

	Battle* battle;

	int click_stepframe = 30;

	mapc = MapControl(1920, 1200, 6, 5, 1, players[0], pc);
	
	file.open("savedata.dat", ios::binary | ios::in);
	file.read((char*)&mapc, sizeof(mapc));
	file.close();
	

	while (!CheckHitKey(KEY_INPUT_ESCAPE) && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		SetDrawScreen(DX_SCREEN_BACK);
		gpUpdateKey();
		mapc.Update();
	}

	file.open("savedata.dat", ios::binary | ios::out);
	file.write((char*)&mapc, sizeof(mapc));
	file.close();
	file.open("allendata.dat", ios::binary | ios::out);
	file.write((char*)players[0], sizeof(mapc));
	file.close();

	DxLib_End(); // �c�w���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��
}