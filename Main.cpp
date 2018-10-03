#include "DxLib.h"
#include "Battle.h" 

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

	Battle();

	DxLib_End(); // �c�w���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��
}