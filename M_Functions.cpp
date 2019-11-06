#include"DxLib.h"
#include"M_Functions.h"

static int Key[256];

int gpUpdateKey() {
	char tmpKey[256];             // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey);  // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;   // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0; // 0�ɂ���
		}
	}
	return 0;
}

int Button(int Keycode) {
	return Key[Keycode];
}

bool AnyButton() {
	for (int i = 0; i < 256; i++) {
		if (Key[i] == 1) {
			return true;
		}
	}
	return false;
}
