#include "draw.h"
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Equipment.h"

typedef uint64_t stagedata;

void battle_stage(stagedata stage) {
	stagedata test = 1 * pow(2, 35);//����l�͈̔͂�36�}�X�Ɍ��肷��
	int image_stage = LoadGraph("battlepanel.png"); //�ʏ�}�X
	int image_stagenot = LoadGraph("not_battlepanel.png"); //�ʍs�s�\�}�X
	int up = 136; //�����y���W
	int left = 496; //�����x���W
	while (test >= 1) {
		if (stage & test) {
			DrawGraph(left, up, image_stage, TRUE);
		}
		else {
			DrawGraph(left, up, image_stagenot, TRUE);
		}
		test /= 2;
		left += 160;
		if (left > 1296) {
			left = 496;

			up += 160;
		}
	}
	DeleteGraph(image_stage);
	DeleteGraph(image_stagenot);
}

void redraw_battle(stagedata stage, Enemy *_enemy, Player *_player) {
	int background = LoadGraph("bg_natural_sougen.jpg"); // �w�i�摜

	DrawGraph(0, 0, background, TRUE);
	battle_stage(stage);
	DrawGraph(_enemy->getX(), _enemy->getY(), _enemy->getImage(), TRUE);
	DrawGraph(_player->getX(), _player->getY(), _player->getImage(), TRUE);

	DeleteGraph(background);
}

void draw_command(int sele) { //�R�}���h�`��̊֐�
	int command = LoadGraph("command.png"); // �R�}���h�p�l��
	int point = LoadGraph("pointer.png"); // �R�}���h�I��p�̃|�C���^�摜

	DrawRotaGraph(200, 400, 2.0, 0, command, TRUE); //�R�}���h�t���[���̕`��
	DrawRotaGraph(120, 220 + 200 * sele, 1.5, 0, point, TRUE); // �I��p�|�C���^�̕`��
	DrawFormatString(150, 200, GetColor(0, 0, 0), "��������");
	DrawFormatString(150, 400, GetColor(0, 0, 0), "���ǂ�");

	DeleteGraph(command);
	DeleteGraph(point);
}

int draw_attackable_area(Player me, Enemy enemy) { // ��ɔz��ɕύX
	int player_x = me.getX(); // �Ώۃv���C���[��x���W
	int player_y = me.getY(); // �Ώۃv���C���[��y���W
	Equipment arm = me.getEquipment();
	int attackable_image = LoadGraph("attackpanel.png");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	if (arm.getAttackable()  == -1) {
		for (int x = 496; x <= 1296; x += 160) {
			for (int y = 136; y <= 936; y += 160) {
				if (! (x == player_x && y == player_y)) {
					DrawGraph(x, y, attackable_image, TRUE);
					if (player_x == x && player_y == y) {
						DrawGraph(me.getX(), me.getY(), me.getImage(), TRUE);
					}
					if (enemy.getX() == x && enemy.getY() == y) {
						DrawGraph(enemy.getX(), enemy.getY(), enemy.getImage(), TRUE);
					}
				}
			}
		}
	}
	else {
		for (int x = -1 * (arm.getAttackable()); x <= arm.getAttackable(); x++) {
			for (int y = -1 * (arm.getAttackable()); y <= arm.getAttackable(); y++) {
				if ((x != 0 || y != 0) && (player_x + 160 * x >= 496 && player_x + 160*x <= 1296) && (player_y + 160*y >= 136 && player_y +160*y <= 936)) {
					DrawGraph(player_x + 160 * x, player_y + 160 * y, attackable_image, TRUE);
				}
			}
		}
	}

	int result = ((player_x - 496) / 160) + ((player_y - 136) / 160) * 10; // �J�[�\���̏����ʒu�͍U���L����

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DeleteGraph(attackable_image);

	return result;
}

void draw_attack_area(int point) {
	int x = point % 10;
	int y = (point - x) / 10;
	int frame = LoadGraph("battleframe.png");
	DrawGraph(496 + 160 * x, 136 + 160 * y, frame, TRUE);

	DeleteGraph(frame);
}
