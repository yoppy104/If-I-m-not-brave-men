#include "DxLib.h"
#include "Battle.h" 
#include "Player.h"
#include "Allen.h"
#include "Craig.h"
#include "Imitia.h"
#include "Rain.h"
#include "Weapon.h"
#include "FireBall.h"

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

	Weapon iron_sword(12, 50, 1, 1, 11); // �����̃N���X
	Weapon wood_bow(8, 50, 1, 2, 11); // �����̃N���X
	Weapon big_axe(15, 50, 1, 1, 11); // �����̃N���X
	Weapon iron_spear(10, 50, 1, 1, 21); // �����̃N���X

	int allen_image = LoadGraph("���m�A��������.png"); //�A�����̉摜
	int rain_image = LoadGraph("�����C������.png"); //���C���̉摜
	int craig_image = LoadGraph("���N���C�O����.png"); //�N���C�O�̉摜
	int imitia_image = LoadGraph("�|�C�~�e�B�A����.png"); //�C�~�e�B�A�̉摜

	Allen allen("�A����", 496 + 160 * 5, 136 + 160 * 5, 20, 7, 3, 6, 5, iron_sword, allen_image, 10); // �A�����̍\���̒�`
	Rain rain("���C��", 496 + 160 * 4, 136 + 160 * 5, 15, 4, 2, 10, 3, iron_spear, rain_image); // ���C���̍\���̒�`
	Craig craig("�N���C�O", 496 + 160 * 0, 136 + 160 * 5, 25, 10, 10, 0, 2, big_axe, craig_image); // �N���C�O�̍\���̒�`
	Imitia imitia("�C�~�e�B�A", 496 + 160 * 1, 136 + 160 * 5, 20, 6, 8, 7, 6, wood_bow, imitia_image); // �C�~�e�B�A�̍\���̒�`
	Player* players[] = { &allen, &rain, &craig, &imitia };
	int size_players = sizeof(players) / sizeof(players[0]);
	for (int i = 1; i < size_players; i++) {
		int j = i;
		while (j > 0 && players[j]->getDex() > players[j - 1]->getDex()) {
			Player* t = players[j - 1];
			players[j - 1] = players[j];
			players[j] = t;
		}
	}

	Battle(players, size_players);



	DxLib_End(); // �c�w���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��
}