#include "DxLib.h"
#include "Battle.h" 
#include "Player.h"
#include "Allen.h"
#include "Craig.h"
#include "Imitia.h"
#include "Rain.h"
#include "Weapon.h"

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

	Weapon iron_sword(10, 50, 1, 1, 11); // �����̃N���X
	int player_image = LoadGraph("�v���C���[.png"); // �v���C���[�̉摜

	Allen allen("�A����", 496 + 160 * 5, 136 + 160 * 5, 20, 7, 3, 6, 5, iron_sword, player_image, 10); // �A�����̍\���̒�`
	Rain rain("���C��", 496 + 160 * 4, 136 + 160 * 5, 15, 4, 2, 10, 3, iron_sword, player_image); // ���C���̍\���̒�`
	Craig craig("�N���C�O", 496 + 160 * 0, 136 + 160 * 5, 25, 10, 10, 0, 2, iron_sword, player_image); // �N���C�O�̍\���̒�`
	Imitia imitia("�C�~�e�B�A", 496 + 160 * 1, 136 + 160 * 5, 20, 6, 8, 7, 6, iron_sword, player_image); // �C�~�e�B�A�̍\���̒�`
	Player players[] = { allen, rain, craig, imitia };

	Battle(players, sizeof(players)/sizeof(players[0]));

	DxLib_End(); // �c�w���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��
}