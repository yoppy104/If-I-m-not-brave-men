#include <vector>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <memory>
#include "DxLib.h"
#include "IDs.h"
#include "M_Functions.h"
#include "MapControll.h"
#include "PartyControll.h"
#include "Battle_Stage.h"

using player_ptr = std::shared_ptr<Player> ;

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR pCmdLine, int CmdShow)
{
	ChangeWindowMode(true);	SetGraphMode(1920, 1200, 32);
	//SetGraphMode(1920, 1200, 32); // �E�B���h�E�T�C�Y���w��
	SetDrawArea(0, 0, 1920, 1200);
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);
	SetMainWindowText("IfNotBraveman"); // �E�B���h�E�^�C�g�����w��
	SetOutApplicationLogValidFlag(FALSE); // ���O���o�Ȃ��悤�ɐݒ�

	if (DxLib_Init() == -1) // DX���C�u�����̏�����
	{
		return -1; // �G���[��f������I��
	}

	SetFontSize(32); // �t�H���g�T�C�Y�̎w��

	ProcessMessage(); // ���荞�ݏ���������Ƃ��ɕK�{

	SRand(time(NULL));

	// �����t�@�C���̓ǂݍ���
	int main = LoadSoundMem("sounds\\SystemBGM\\Opening.mp3"); //���C���e�[�}
	ChangeVolumeSoundMem(100, main);

	//�p�[�e�B�[�C���X�^���X�𐶐�����B
	player_ptr allen(new Player(ALLEN, 496 + 160 * 5, 136 + 160 * 5));
	std::vector<player_ptr> players = { allen };
	std:: shared_ptr<PartyControll> pc(new PartyControll(players, 0, 1000));

	//�o�g���̃C���X�^���X�𐶐�����B
	std::unique_ptr<Battle_Stage> battle_stage(new Battle_Stage(pc));

	int mode = TITLE;

	//20 40
	std::unique_ptr<MapControll> mapc(new MapControll(1920, 1200, 20, 40, 1, players[0], pc));

	int image_title = LoadGraph("images\\BackGround\\�^�C�g��1920 1200.png");

	mode = TITLE;

	int enemy_infomation = 0;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && Button(KEY_INPUT_ESCAPE) < 50) {
		SetDrawScreen(DX_SCREEN_BACK);
		gpUpdateKey();
		switch (mode) {
		case TITLE://�^�C�g�����
			if (!CheckSoundMem(main)) {
				PlaySoundMem(main, DX_PLAYTYPE_LOOP, TRUE);
			}
			DrawGraph(0, 0, image_title, TRUE);
			if (AnyButton()) {//�C�ӂ̃L�[����������A�}�b�v��ʂɑJ�ڂ���B
				mode = MAP_NORMAL;
				StopSoundMem(main);
			}
			break;
		case MAP_NORMAL://�}�b�v���
			enemy_infomation = mapc->Update();
			if (enemy_infomation) {
				mode = BATTLE_START;
			}
			break;
		case BATTLE_START://�o�g�����
			int battle = battle_stage->Battle_Update(enemy_infomation);
			if (battle == 1) {
				mode = MAP_NORMAL;
			}
			else if (battle == -1) {
				mode = TITLE;
			}
			break;
		}
		
		if (Button(KEY_INPUT_ESCAPE) != 0) {
			DrawFormatString(10, 10, GetColor(0, 0, 0), "�Q�[�����I�����܂�");
		}
	}

	InitSoundMem();
	DxLib_End(); // �c�w���C�u�����g�p�̏I������
	return 0; // �\�t�g�̏I��
}