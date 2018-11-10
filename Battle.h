#pragma once
#include "vector"
#include "Player.h"
#include "Enemy.h"
/*
void Battle(Player** players, int size_players);*/

using namespace std;
typedef unsigned long long stagedata;

class Battle {
private:
	vector <Enemy*> enemys; //�G�l�~�[�x�N�^�[
	vector <Player*> players; //�v���C���[�x�N�^�[
	stagedata stage; //�X�e�[�W
	int select; //�I��ԍ�
	int next_player; //���̃v���C���[�̃C���f�b�N�X
	int next_enemy; //���̃G�l�~�[�̃C���f�b�N�X
	Character* turn_character; //�^�[���̃L�����N�^�[

	//�`��֐�
	void draw_command_do(); //�S�̂̍s���̃R�}���h��`��
	void draw_command(); //�P�̂̍s���̃R�}���h��`��

	//�摜
	int command_image; //�R�}���h�����̉摜
	int point_image; //�|�C���^�̉摜
	//�v���C���[�̃X�e�[�^�X��\�����镔���̉摜
	int playerpanel_image_blue;
	int playerpanel_image_red;
	int playerpanel_image_gray;
	int background; // �w�i�摜

public:
	Battle(); //�R���X�g���N�^
	Battle(vector <Player*> player); //�R���X�g���N�^
	~Battle(); //�f�X�g���N�^

	vector <Enemy*> getEnemys(); //�G�l�~�[�z���Ԃ�
	Enemy* getEnemy(int index); //�G�l�~�[�P�̂̃|�C���^��Ԃ��B
	int getNumEnemys(); //�G�l�~�[�̑�����Ԃ��B
	int getSelect(); //select�ϐ���Ԃ��B

	void minusSelect(); //select�ϐ���-1
	void plusSelect(); //select�ϐ���+1

	void Update(int mode); //�`�擙�̍X�V
	void changeNextCharacter(); //���̃L�����N�^�[���X�V
	void select_init_(); //select�ϐ���������

	int select_do_player();
};