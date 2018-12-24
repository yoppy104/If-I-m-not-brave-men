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

#include <iostream>
#include "Mathematic.h"
#include "MapControl.h"
#include "WoodSword.h"

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

	MapControl mapc(5, 5, 1);
	
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
	Rain rain("���C��", 496 + 160 * 4, 136 + 160 * 5, 15, 4, 4, 10, 3, WoodSword(), rain_image, rain_image_dead); // ���C���̍\���̒�`
	Craig craig("�N���C�O", 496 + 160 * 0, 136 + 160 * 5, 25, 10, 7, 0, 2, WoodSword(), craig_image, craig_image_dead); // �N���C�O�̍\���̒�`
	Imitia imitia("�C�~�e�B�A", 496 + 160 * 1, 136 + 160 * 5, 20, 6, 8, 7, 6, WoodSword(), imitia_image, imitia_image_dead); // �C�~�e�B�A�̍\���̒�`
	vector <Player*> players = { &allen, &rain, &craig, &imitia };
	for (int i = 1; i < players.size(); i++) {
		int j = i;
		while (j > 0 && players[j]->getDex() > players[j - 1]->getDex()) {
			Player* t = players[j - 1];
			players[j - 1] = players[j];
			players[j] = t;
		}
	}

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

	while (!CheckHitKey(KEY_INPUT_ESCAPE) && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		SetDrawScreen(DX_SCREEN_BACK);

		//�e�폈��
		if (mode == TITLE) { //�^�C�g����ʎ��̏���
			if (!CheckSoundMem(main)) {
				PlaySoundMem(main, DX_PLAYTYPE_LOOP, TRUE); //���C���e�[�}�����[�v�Đ�
			}
			DrawGraph(-100, 0, title_image, TRUE);
		}
		else if (mode == BATTLE_START) { //�o�g���J�n���̏���
			PlaySoundMem(battle_bgm, DX_PLAYTYPE_LOOP, TRUE); //�o�g��BGM�����[�v�Đ�
			battle = new Battle(players); //�o�g���N���X�𐶐�
			drawmode = DRAW_BATTLE; //�`�惂�[�h���o�g���Ɉڍs
			mode = BATTLE_DO_SELECT; //�v���C���[�̍s���I���Ɉڍs
		}
		else if (mode == BATTLE_END) { //�o�g���I�����̏���
			battle->~Battle(); //�o�g���N���X�̃f�X�g���N�^
			delete battle; //�o�g���N���X�̃����������
		}

		if (click_stepframe < 30) { //�N���b�N�\�ɂȂ�܂ł̎��Ԃ����Z����
			click_stepframe++;
		}
		else {
			int temp[2] = {1920, 1200};
			mapc.show(temp, players[0]);
		}

		//�`�揈��
		if (drawmode == DRAW_BATTLE) {
			battle->Update(mode); //�o�g���̕`����X�V
		}


		//�L�[���͏���

		if (click_stepframe >= 30) {
			char input_key[256];
			GetHitKeyStateAll(input_key); //���͒l���擾
			if (input_key[KEY_INPUT_UP] == 1) { // ��L�[
				click_stepframe = 0;
				if (mode == BATTLE_DO_SELECT) { //�o�g�����̃v���C���[�S�̂̍s�����莞
					if (battle->getSelect() - 1 >= 0) {
						PlaySoundMem(button_se, DX_PLAYTYPE_BACK, TRUE); //�J�[�\���̈ړ���
						battle->minusSelect();
					}
					else {
						PlaySoundMem(sound_cancel, DX_PLAYTYPE_BACK, TRUE); //�G���[��
					}
				}
			}
			if (input_key[KEY_INPUT_DOWN] == 1) { //���L�[
				click_stepframe = 0;
				if (mode == BATTLE_DO_SELECT) { //�o�g�����̃v���C���[�S�̂̍s�����莞
					if (battle->getSelect() + 1 <= 1) {
						PlaySoundMem(button_se, DX_PLAYTYPE_BACK, TRUE); //�J�[�\���̈ړ���
						battle->plusSelect();
					}
					else {
						PlaySoundMem(sound_cancel, DX_PLAYTYPE_BACK, TRUE); //�G���[��
					}
				}
			}
			if (input_key[KEY_INPUT_RIGHT] == 1) { //�E�L�[
				click_stepframe = 0;

			}
			if (input_key[KEY_INPUT_LEFT] == 1) { //���L�[
				click_stepframe = 0;

			}
			if (input_key[KEY_INPUT_SPACE] == 1) { //�X�y�[�X�L�[
				click_stepframe = 0;
				if (mode == TITLE) {
					StopSoundMem(main);
					mode = 0;
				}
				else if (mode == BATTLE_DO_SELECT) {
					switch (battle->select_do_player()) {
					case 0:
						mode = BATTLE_DO_PLAYER;
						break;
					case 1:
						mode = TITLE;//��ŕύX
						break;
					case 2:
						mode = BATTLE_ENEMY_TURN;
						mode = TITLE;
						break;
					}
				}
			}
			if (input_key[KEY_INPUT_B] == 1) { // B�L�[
				click_stepframe = 0;

			}
		}
	}
	StopSoundMem(main);

	DxLib_End(); // �c�w���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��
}