#include "DxLib.h"
#include "Battle.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "Weapon.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "draw.h"
#include "Mathematic.h"

typedef uint8_t datatable;
typedef unsigned long long stagedata;

//�{��
void Battle(Player* players, int size_players)
{
	int enemy_image = LoadGraph("enemy.png"); // �G�̉摜
	int frame_image = LoadGraph("battleframe->png"); // �U���͈͂̑I��p

	//�X�e�[�W�̃f�[�^�l
	stagedata stage = 0b1111111111111111111011111111111111111;

	int battlemap_left = 496; // �}�b�v�̍��̍��W
	int battlemap_top = 136; // �}�b�v�̏�̍��W

	Enemy enemy_a("�X���C��", 496 + 160 * 2, 136 + 160 * 0, 5, 2, 100, 2, 4, enemy_image); // �X���C���̍\���̒�`
	Enemy enemy_b("�X���C��", 496 + 160 * 0, 136 + 160 * 0, 5, 2, 100, 2, 4, enemy_image); // �X���C���̍\���̒�`
	Enemy enemy_c("�X���C��", 496 + 160 * 1, 136 + 160 * 0, 5, 2, 100, 2, 4, enemy_image); // �X���C���̍\���̒�`
	Enemy enemy[3] = { enemy_a, enemy_b, enemy_c };

	int size_enemy = sizeof(enemy) / sizeof(enemy[0]);

	int select_do; //�O���[�v�S�̂ł̍s���I��
	int select; //�l�ł̍s���I��
	bool is_loop = true;
	while (is_loop && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		select_do = 0; //0:�s��,�@1:������
		ClearDrawScreen();
		redraw_battle(stage, enemy, size_enemy, players, size_players);
		draw_command_do(select_do); //�R�}���h�g��`��
		while (CheckHitKey(KEY_INPUT_SPACE) == 0) {
			if (CheckHitKey(KEY_INPUT_UP)) {
				if (select_do == 1) {
					select_do--;
					ClearDrawScreen();
					redraw_battle(stage, enemy, size_enemy, players, size_players);
					draw_command_do(select_do);
				}
				while (CheckHitKey(KEY_INPUT_UP)) {}
			}
			else if (CheckHitKey(KEY_INPUT_DOWN)) {
				if (select_do == 0) {
					select_do++;
					ClearDrawScreen();
					redraw_battle(stage, enemy, size_enemy, players, size_players);
					draw_command_do(select_do);
				}
				while (CheckHitKey(KEY_INPUT_DOWN)) {}
			}
		}
		while (CheckHitKey(KEY_INPUT_SPACE)){}

		if (select_do == 0) { //�퓬���s���ꍇ

			//�s������

			//�����܂�


			for (int i = 0; i < 1; i++) {

				int side = 0 / 10; //�ǂ����T�C�h��
				int person = 0 % 10; //�e�T�C�h�̂ǂ̐l��

				if (side == 0) { //�����T�C�h�̍s��
					Player *me = &players[person];
					select = 0; // 0:�U�� 1:���ǂ� 2:�A�C�e�� 3:�h��
					ClearDrawScreen();
					redraw_battle(stage, enemy, size_enemy, players, size_players);
					draw_command(select); //�R�}���h�g��`��

					// �s���̑I��
					while (CheckHitKey(KEY_INPUT_SPACE) == 0 && CheckHitKey(KEY_INPUT_B) == 0) { // space���������猈��
						if (CheckHitKey(KEY_INPUT_DOWN)) { // ������������select��+1
							if (select == 0) {
								select++;
								ClearDrawScreen();
								redraw_battle(stage, enemy, size_enemy, players, size_players);
								draw_command(select);
							}
							while (CheckHitKey(KEY_INPUT_DOWN)) {}
						}
						else if (CheckHitKey(KEY_INPUT_UP)) { // �����������select���\1
							if (select == 1) {
								select--;
								ClearDrawScreen();
								redraw_battle(stage, enemy, size_enemy, players, size_players);
								draw_command(select);
							}
							while (CheckHitKey(KEY_INPUT_UP)) {}
						}
					}
					while (CheckHitKey(KEY_INPUT_B)) {
						select = -1;
					}
					while (CheckHitKey(KEY_INPUT_SPACE)) {}

					redraw_battle(stage, enemy, size_enemy, players, size_players);

					if (select == 0) { //�ʏ�U��
						int point = draw_attackable_area(me, players, size_players, enemy, size_enemy);
						draw_attack_area(point, me);
						while (CheckHitKey(KEY_INPUT_SPACE) == 0) {
							if (CheckHitKey(KEY_INPUT_RIGHT)) {
								if ((point % 10) + 1 < 6) {
									if (me->is_attackable(point + 1)) {
										point += 1;
										ClearDrawScreen();
										redraw_battle(stage, enemy, size_enemy, players, size_players);
										draw_attackable_area(me, players, size_players, enemy, size_enemy);
										draw_attack_area(point, me);
									}
								}
								while (CheckHitKey(KEY_INPUT_RIGHT)) {}
							}
							else if (CheckHitKey(KEY_INPUT_LEFT)) {
								if ((point % 10) - 1 >= 0) {
									if (me->is_attackable(point - 1)) {
										point -= 1;
										ClearDrawScreen();
										redraw_battle(stage, enemy, size_enemy, players, size_players);
										draw_attackable_area(me, players, size_players, enemy, size_enemy);
										draw_attack_area(point, me);
									}
								}
								while (CheckHitKey(KEY_INPUT_LEFT)) {}
							}
							else if (CheckHitKey(KEY_INPUT_UP)) {
								if ((point / 10) - 1 >= 0) {
									if (me->is_attackable(point - 10)) {
										point -= 10;
										ClearDrawScreen();
										redraw_battle(stage, enemy, size_enemy, players, size_players);
										draw_attackable_area(me, players, size_players, enemy, size_enemy);
										draw_attack_area(point, me);
									}
								}
								while (CheckHitKey(KEY_INPUT_UP)) {}
							}
							else if (CheckHitKey(KEY_INPUT_DOWN)) {
								if ((point / 10) + 1 < 6) {
									if (me->is_attackable(point + 10)) {
										point += 10;
										ClearDrawScreen();
										redraw_battle(stage, enemy, size_enemy, players, size_players);
										draw_attackable_area(me, players, size_players, enemy, size_enemy);
										draw_attack_area(point, me);
									}
								}
								while (CheckHitKey(KEY_INPUT_DOWN)) {}
							}
						}
						while (CheckHitKey(KEY_INPUT_SPACE)) {}

						me->battle(point, me,size_players, enemy, size_enemy);
					}
					else if (select == 1) { //�ړ�

						int movelimit = me->getDex();

						while (movelimit > 0 && CheckHitKey(KEY_INPUT_A) == 0) {
							if (CheckHitKey(KEY_INPUT_UP)) {
								if (me->move(0, -160, stage, enemy, size_enemy, players, size_players)) {
									movelimit--;
									ClearDrawScreen();
									redraw_battle(stage, enemy, size_enemy, players, size_players);
								}
								while (CheckHitKey(KEY_INPUT_UP)) {}
							}
							else if (CheckHitKey(KEY_INPUT_DOWN)) {
								if (me->move(0, -160, stage, enemy, size_enemy, players, size_players)) {
									movelimit--;
									ClearDrawScreen();
									redraw_battle(stage, enemy, size_enemy, players, size_players);
								}
								while (CheckHitKey(KEY_INPUT_DOWN)) {}
							}
							else if (CheckHitKey(KEY_INPUT_RIGHT)) {
								if (me->move(160, 0, stage, enemy, size_enemy, players, size_players)) {
									movelimit--;
									ClearDrawScreen();
									redraw_battle(stage, enemy, size_enemy, players, size_players);
								}
								while (CheckHitKey(KEY_INPUT_RIGHT)) {}
							}
							else if (CheckHitKey(KEY_INPUT_LEFT)) {
								if (me->move(-160, 0, stage, enemy, size_enemy, players, size_players)) {
									movelimit--;
									ClearDrawScreen();
									redraw_battle(stage, enemy, size_enemy, players, size_players);
								}
								while (CheckHitKey(KEY_INPUT_LEFT)) {}
							}
						}
					}
				}
				else if (side == 1) {
					DrawFormatString(100, 100, GetColor(0, 0, 0), "enemy_turn");
					WaitTimer(300);
				}
			}
		}
		else if (select_do == 1) { //������ꍇ
			if (GetRand(100) < 50) {
				DrawFormatString(100, 100, GetColor(0, 0, 0), "run");
				WaitTimer(150);
				is_loop = false;
			}
			else {
				DrawFormatString(100, 100, GetColor(0, 0, 0), "don't run");
				WaitTimer(150);
			}
		}
	}
	if (enemy->getHp() < 0) {
		DrawFormatString(100, 100, GetColor(0, 0, 0), "end");
		WaitTimer(150);
		is_loop = false;
	}

	InitGraph();
}



