#include "DxLib.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "Equipment.h"
#include "Player.h"
#include "Enemy.h"
#include "draw.h"

using namespace std;

typedef uint8_t datatable;
typedef unsigned long long stagedata;
//komenntokakuyo

//�{��
int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR pCmdLine, int CmdShow)
{

	SRand(time(NULL));

	ChangeWindowMode(true); // �E�C���h�E���[�h�ɕύX
	SetGraphMode(1920, 1200, 32); // �E�B���h�E�T�C�Y���w��
	SetMainWindowText("NotBraveman"); // �E�B���h�E�^�C�g�����w��
	SetOutApplicationLogValidFlag(FALSE); // ���O���o�Ȃ��悤�ɐݒ�

	if (DxLib_Init() == -1) // DX���C�u�����̏�����
	{
		return -1; // �G���[��f������I��
	}

	int enemy_image = LoadGraph("enemy.png"); // �G�̉摜
	int player_image = LoadGraph("�v���C���[.png"); // �v���C���[�̉摜
	int frame_image = LoadGraph("battleframe.png"); // �U���͈͂̑I��p

	//�X�e�[�W�̃f�[�^�l
	stagedata stage = 0b1111111111111111111011111111111111111;

	//��Q���̐ݒ�
	int block = 0;
	if (block != 0) {
		stagedata test = 1;
		for (int i = 0; i < block; i++) {
			int r = rand() % 36;
			stagedata key = pow(2, r);
			test |= key;
		}
		stage = ~(stage & test);
	}



	int battlemap_left = 496; // �}�b�v�̍��̍��W
	int battlemap_top = 136; // �}�b�v�̏�̍��W

	Equipment iron_sword(true, 10, 50, 1, -1, 42 ); // �����̃N���X

	Player allen("allen", 100, battlemap_left + 160 * 5, battlemap_top + 160 * 5, 10, 2, iron_sword, player_image, 50); // �A�����̍\���̒�`

	Enemy slime("slime", 50, battlemap_left + 160 * 2, battlemap_top + 160 * 3, 2, 1, enemy_image); // �X���C���̍\���̒�`

	redraw_battle(stage, &slime, &allen); // �ĕ`��

	SetFontSize(32); // �t�H���g�T�C�Y�̎w��

	ProcessMessage(); // ���荞�ݏ���������Ƃ��ɕK�{

	int select;
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) { // escape����͂�����Q�[���I��
		select = 0; // 0:�U�� 1:���ǂ� 2:�A�C�e�� 3:�h��
		ClearDrawScreen();
		redraw_battle(stage, &slime, &allen);
		draw_command(select); //�R�}���h�g��`��

		// �s���̑I��
		while (CheckHitKey(KEY_INPUT_SPACE) == 0) { // space���������猈��
			if (CheckHitKey(KEY_INPUT_DOWN)) { // ������������select��+1
				if (select == 0) {
					select++;
					ClearDrawScreen();
					redraw_battle(stage, &slime, &allen);
					draw_command(select);
				}
				while(CheckHitKey(KEY_INPUT_DOWN)){}
			}
			else if (CheckHitKey(KEY_INPUT_UP)) { // �����������select���\1
				if (select == 1) {
					select--;
					ClearDrawScreen();
					redraw_battle(stage, &slime, &allen);
					draw_command(select);
				}
				while(CheckHitKey(KEY_INPUT_UP)){}
			}
		}
		while (CheckHitKey(KEY_INPUT_SPACE)) {}

		redraw_battle(stage, &slime, &allen);

		if (select == 0) { //�ʏ�U��
			int point = draw_attackable_area(allen, slime);
			draw_attack_area(point, allen);
			while(CheckHitKey(KEY_INPUT_SPACE) == 0){
				if (CheckHitKey(KEY_INPUT_RIGHT)) {
					if ((point % 10) + 1 < 6) {
						if (allen.is_attackable(point + 1)) {
							point += 1;
							ClearDrawScreen();
							redraw_battle(stage, &slime, &allen);
							draw_attackable_area(allen, slime);
							draw_attack_area(point, allen);
						}
					}
					while (CheckHitKey(KEY_INPUT_RIGHT)) {}
				}
				else if (CheckHitKey(KEY_INPUT_LEFT)) {
					if ((point % 10) - 1 >= 0) {
						if (allen.is_attackable(point - 1)) {
							point -= 1;
							ClearDrawScreen();
							redraw_battle(stage, &slime, &allen);
							draw_attackable_area(allen, slime);
							draw_attack_area(point, allen);
						}
					}
					while (CheckHitKey(KEY_INPUT_LEFT)) {}
				}
				else if (CheckHitKey(KEY_INPUT_UP)) {
					if ((point / 10) - 1 >= 0) {
						if (allen.is_attackable(point - 10)) {
							point -= 10;
							ClearDrawScreen();
							redraw_battle(stage, &slime, &allen);
							draw_attackable_area(allen, slime);
							draw_attack_area(point, allen);
						}
					}
					while (CheckHitKey(KEY_INPUT_UP)) {}
				}
				else if (CheckHitKey(KEY_INPUT_DOWN)) {
					if ((point / 10) + 1 < 6) {
						if (allen.is_attackable(point + 10)) {
							point += 10;
							ClearDrawScreen();
							redraw_battle(stage, &slime, &allen);
							draw_attackable_area(allen, slime);
							draw_attack_area(point, allen);
						}
					}
					while (CheckHitKey(KEY_INPUT_DOWN)) {}
				}
			}
			while(CheckHitKey(KEY_INPUT_SPACE)){}

			allen.battle(point, &allen, &slime);
		}
		else if (select == 1) { //�ړ�

			int movelimit = allen.getDex();

			while (movelimit > 0 && CheckHitKey(KEY_INPUT_A) == 0) {
				if (CheckHitKey(KEY_INPUT_UP)) {
					if (allen.move(0, -160, stage, slime, allen)) {
						movelimit--;
						ClearDrawScreen();
						redraw_battle(stage, &slime, &allen);
					} 
					while (CheckHitKey(KEY_INPUT_UP)){}
				}
				else if (CheckHitKey(KEY_INPUT_DOWN)) {
					if (allen.move(0, 160, stage, slime, allen)) {
						movelimit--;
						ClearDrawScreen();
						redraw_battle(stage, &slime, &allen);
					}
					while (CheckHitKey(KEY_INPUT_DOWN)) {}
				}
				else if (CheckHitKey(KEY_INPUT_RIGHT)) {
					if (allen.move(160, 0, stage, slime, allen)) {
						movelimit--;
						ClearDrawScreen();
						redraw_battle(stage, &slime, &allen);
					}
					while (CheckHitKey(KEY_INPUT_RIGHT)) {}
				}
				else if (CheckHitKey(KEY_INPUT_LEFT)) {
					if (allen.move(-160, 0, stage, slime, allen)) {
						movelimit--;
						ClearDrawScreen();
						redraw_battle(stage, &slime, &allen);
					}
					while (CheckHitKey(KEY_INPUT_LEFT)) {}
				}
			}
		}
		if (slime.getHp() < 0) {
			DrawFormatString(100, 100, GetColor(0, 0, 0), "end");
			WaitTimer(150);
			return 0;
		}
	}

	InitGraph();
	DxLib_End(); // �c�w���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��
}



