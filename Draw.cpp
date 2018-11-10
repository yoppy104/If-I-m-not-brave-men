#define PI 3.14159263

#include "draw.h"
#include <math.h>
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"

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

void draw_param(int x, int y, Player* player, int image) {
	DrawGraph(x, y, image, TRUE);
	int col = GetColor(255, 255, 255);
	player->getName(x + 10, y + 10, col);
	DrawFormatString(x + 10, y + 50, col, "HP : %d / %d", (player->getHp() > 0) ? player->getHp() : 0, player->getHpMax());
	if (player->getHasMp()) {
		DrawFormatString(x + 10, y + 90, col, "MP : %d", player->getMp());
	}
	else {
		DrawFormatString(x + 10, y + 90, col, "MP : %d", player->getMagicStone());
	}
}


void redraw_battle(stagedata stage, Enemy **_enemy, int size_enemy, Player **_player, int size_player) {
	/*
	int background = LoadGraph("�퓬�w�i_����.jpg"); // �w�i�摜

	DrawGraph(0, 0, background, TRUE);
	battle_stage(stage);
	for (auto itr_p = players.begin; i < size_enemy; i++) {
		if (_enemy[i]->getIsMoveable()) {
			DrawGraph(_enemy[i]->getX(), _enemy[i]->getY(), _enemy[i]->getImage(), TRUE);
		}
		else {
			DrawGraph(_enemy[i]->getX(), _enemy[i]->getY(), _enemy[i]->getImageDead(), TRUE);
		}
	}

	int image;
	for (int i = 0; i < size_player; i++) {
		if (_player[i]->getIsMoveable()) {
			DrawGraph(_player[i]->getX(), _player[i]->getY(), _player[i]->getImage(), TRUE);
			if ((_player[i]->getHp() / _player[i]->getHpMax()) > 0.2) {
				image = LoadGraph("playerdata_blue.png");
				draw_param(1500, 100 + 150 * i, _player[i], image);
			}
			else {
				image = LoadGraph("playerdata_red.png");
				draw_param(1500, 100 + 150 * i, _player[i], image);
			}
		}
		else {
			DrawGraph(_player[i]->getX(), _player[i]->getY(), _player[i]->getImageDead(), TRUE);
			image = LoadGraph("playerdata_gray.png");
			draw_param(1500, 100 + 150 * i, _player[i], image);
		}
	}

	DeleteGraph(background);
	*/
}

void draw_command(int sele) { //�R�}���h�`��̊֐�
	int command = LoadGraph("command.png"); // �R�}���h�p�l��
	int point = LoadGraph("pointer.png"); // �R�}���h�I��p�̃|�C���^�摜

	DrawRotaGraph(200, 400, 2.0, 0, command, TRUE); //�R�}���h�t���[���̕`��
	DrawRotaGraph(120, 220 + 100 * sele, 1.5, 0, point, TRUE); // �I��p�|�C���^�̕`��
	DrawFormatString(150, 200, GetColor(0, 0, 0), "��������");
	DrawFormatString(150, 300, GetColor(0, 0, 0), "���ǂ�");
	DrawFormatString(150, 400, GetColor(0, 0, 0), "���p");

	DeleteGraph(command);
	DeleteGraph(point);
}

void draw_command_do(int sele) {
	int command = LoadGraph("command.png"); // �R�}���h�p�l��
	int point = LoadGraph("pointer.png"); // �R�}���h�I��p�̃|�C���^�摜

	DrawRotaGraph(200, 400, 2.0, 0, command, TRUE); //�R�}���h�t���[���̕`��
	DrawRotaGraph(120, 220 + 200 * sele, 1.5, 0, point, TRUE); // �I��p�|�C���^�̕`��
	DrawFormatString(150, 200, GetColor(0, 0, 0), "����Ƃ�");
	DrawFormatString(150, 400, GetColor(0, 0, 0), "�Ƃ�����");

	DeleteGraph(command);
	DeleteGraph(point);
}

int draw_attackable_area(Player* me, Player** players, int size_players, Enemy** enemy, int size_enemy, int is_weapon) { // ��ɔz��ɕύX
	int player_x = me->getX(); // �Ώۃv���C���[��x���W
	int player_y = me->getY(); // �Ώۃv���C���[��y���W
	Weapon arm = me->getWeapon();
	int attackable_area;
	if (is_weapon == 0) {
		attackable_area = arm.getAttackable();
	}
	else {
		attackable_area = is_weapon;
	}
	int attackable_image = LoadGraph("attackpanel.png");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	if (attackable_area  == -1) {
		for (int x = 496; x <= 1296; x += 160) {
			for (int y = 136; y <= 936; y += 160) {
				if (! (x == player_x && y == player_y)) {
					DrawGraph(x, y, attackable_image, TRUE);
				}
			}
		}
	}
	else {
		for (int x = -1 * (attackable_area); x <= attackable_area; x++) {
			for (int y = -1 * (attackable_area); y <= attackable_area; y++) {
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

void draw_attack_area(int point, Player* me, int is_magic) {
	int x = point % 10; //�J�[�\����x���W
	int y = point / 10; //�J�[�\����y���W
	int attack_area = LoadGraph("frame.png"); //�U���p�l��
	int frame = LoadGraph("battleframe.png"); //�t���[��
	int area;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 184);
	if (is_magic) {
		area = is_magic;
	}
	else {
		area = me->getWeapon().getAttackArea();
	}

	if (496 + 160 * x != me->getX() || 136 + 160 * y != me->getY()) {
		int style = area / 10;
		int len = area % 10;
		if (style == 1) { //����̍U���͈͂�1�̎���
			DrawGraph(496 + 160 * x, 136 + 160 * y, attack_area, TRUE);
		}
		else if (style == 2) {
			int delta_x = (-me->getX() + (496 + 160 * x) == 0) ? 0 : (-me->getX() + (496 + 160 * x)) / abs(-me->getX() + (496 + 160 * x));
			int delta_y = (-me->getY() + (136 + 160 * y) == 0) ? 0 : (-me->getY() + (136 + 160 * y)) / abs(-me->getY() + (136 + 160 * y));
			for (int i = 0; i < len + 1; i++) {
				DrawGraph(496 + 160 * (x + delta_x * i), 136 + 160 * (y + delta_y * i), attack_area, TRUE);
			}
		}
		else if (style == 3) {
			//�U���͈͂�L�΂�����������
			int delta_x = -me->getY() + (136 + 160 * y);
			int delta_y = -me->getX() + (496 + 160 * x);
			if (delta_x == 0) delta_y = 1;
			if (delta_y == 0) delta_x = 1;
			if ((delta_x < 0 && delta_y < 0) || (delta_x > 0 && delta_y > 0)) {
				delta_x = 1;
				delta_y = -1;
			}
			else if ((delta_x < 0 && delta_y > 0) || (delta_x > 0 && delta_y < 0)) {
				delta_x = 1;
				delta_y = 1;
			}
			//�����܂�
			for (int i = 0; i < len + 1; i++) {
				if (x + delta_x * i >= 0 && x + delta_x * i < 6 && y + delta_y * i >= 0 && y + delta_y * i < 6) { //�͈͊O�͕`�悵�Ȃ�
					DrawGraph(496 + 160 * (x + delta_x * i), 136 + 160 * (y + delta_y * i), attack_area, TRUE);
				}
				if (x - delta_x * i >= 0 && x - delta_x * i < 6 && y - delta_y * i >= 0 && y - delta_y * i < 6) { //�͈͊O�͕`�悵�Ȃ�
					DrawGraph(496 + 160 * (x - delta_x * i), 136 + 160 * (y - delta_y * i), attack_area, TRUE);
				}
			}
		}
		else if (style == 4) {
			for (int delta_x = -len; delta_x < len+1; delta_x++) {
				for (int delta_y = -len; delta_y < len + 1; delta_y++) {
					if (x - delta_x >= 0 && x - delta_x < 6 && y - delta_y >= 0 && y - delta_y < 6) {
						DrawGraph(496 + 160 * (x - delta_x), 136 + 160 * (y - delta_y), attack_area, TRUE);
					}
				}
			}
		}

	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(496 + 160 * x, 136 + 160 * y, frame, TRUE);

	DeleteGraph(frame);
	DeleteGraph(attack_area);
}

void draw_magic_select(int select) {
	int pointa_image = LoadGraph("pointer.png");
	int x = (select > 8) ? 1 : 0;
	DrawGraph(510 + 300 * x, 200 + 50 * (select % 9), pointa_image, TRUE);
}


void draw_attack_animation(int attack_x, int attack_y, int pos_x, int pos_y, int type, int frame) {
	if (type == 0) {
		int image = LoadGraph("slash7.png");
		DrawGraph(attack_x + 20 - 10 * frame, attack_y - 20 + 10 * frame, image, TRUE);
	}
	else if (type == 1) {
		int image = LoadGraph("slash7.png");
		double rota = 0;
		int dx = attack_x - pos_x;
		int dy = attack_y - pos_y;

		if (dx == 0) {
			rota = - PI / 4;
		}
		else if (dy == 0) {
			rota = PI / 4;
		}
		else if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
			rota = PI / 2;
		}

		DrawRotaGraph(pos_x + (dx / 4) * 2 * frame + 64, pos_y + (dy / 4) * 2 * frame + 64, 1.0, rota, image, TRUE, FALSE);
	}
	else if (type == 2) {
		int image = LoadGraph("arrow.png");
		double rota = 0;
		int dx = attack_x - pos_x;
		int dy = attack_y - pos_y;

		if (dx == 0) {
			if (dy > 0) {
				rota = -PI / 4 * 3;
			}
			else {
				rota = PI / 4;
			}
		}
		else if (dy == 0) {
			if (dx > 0) {
				rota = PI / 4 * 3;
			}
			else {
				rota = -PI / 4;
			}
		}
		else if (dx > 0 && dy < 0) {
			rota = -PI / 2;
		}
		else if (dx > 0 && dy > 0) {
			rota = PI;
		}
		else if (dx < 0 && dy > 0) {
			rota = PI / 2;
		}

		DrawRotaGraph(pos_x + (dx / 4) * frame + 64, pos_y + (dy / 4) * frame + 64, 1.0, rota, image, TRUE, FALSE);
	}
	else if (type == 3) {
		int image = LoadGraph("slash7.png");
		DrawRotaGraph(attack_x + 64, attack_y + 20 - 20 + 10 * frame, 1.0, PI / 4 * 3, image, TRUE, FALSE);
	}
	else if (type == 4) {
		int image = LoadGraph("fireball.png");
		int dx = attack_x - pos_x;
		int dy = attack_y - pos_y;
		DrawGraph(pos_x + (dx / 4) * frame, pos_y + (dy / 4) * frame, image, TRUE);
	}
}