#pragma once

#include "Map.h"
#include "Player.h"
#include "Menu.h"
#include <vector>

//�v���C���[�̌����Ă������
enum DirectionPlayer {
	FRONT,
	BACK,
	RIGHT,
	LEFT
};

//�}�b�v����p�̃N���X�BMap�N���X��z��Ƃ��ĊǗ�����B
class MapControl {
private:

	//����
	using Sound = struct {
		int main;
		int walk;
		int error;
		int enter;
	};

	//�}�b�v�T�C�Y
	using MapSize = struct {
		int width;
		int height;
	};

	//�f�B�X�v���C�T�C�Y
	using DispSize = struct {
		int width;
		int height;
	};

	// �v���C���[�̃}�b�v��ł̍��W
	Vector positionPlayer;

	//�v���C���[�̌����Ă������
	DirectionPlayer directionPlayer;

	//�}�b�v�̑S�̏c���̃s�N�Z����
	MapSize mapSize;

	//�f�B�X�v���C�̏c���̃s�N�Z����
	DispSize dispSize;

	//���݂̃t���[��
	//�A�j���[�V�����p
	int countFrame;

	//�}�b�v�������ׂĊi�[�����R���e�i
	std::vector <std::vector<std::shared_ptr<Map>>> maps;

	//�v���C���[�̑�\�C���X�^���X
	std::shared_ptr<Player> allen;

	//���ݎ��s���̃C�x���g
	std::shared_ptr<Event> nowEvent;

	//�}�b�v�ɕ\�������NPC
	std::vector<std::shared_ptr<NPC>> npcs;

	//�ړ��\���ǂ�����bool
	bool isMove;

	//�C�x���g�����������ǂ�����bool
	bool isEvent;

	//��b�����������ǂ�����bool
	bool isChat;

	//���j���[�����������ǂ�����bool
	bool isMenu;

	//�}�b�v�̉摜
	int mapImage;

	//���݉�b����NPC
	std::shared_ptr<NPC> nowChat;

	//���j���[�N���X�̃C���X�^���X��ێ�
	std::shared_ptr<Menu> menu;

	//�p�[�e�B�Ǘ��N���X�̃C���X�^���X��ێ�
	std::shared_ptr<PartyControl> pc;

	Sound sounds;

public:
	MapControl() = default;
	MapControl(int width, int height, int x, int y, int map, std::shared_ptr<Player> allen, std::shared_ptr<PartyControl> pc);
	~MapControl();
	int getX() const { positionPlayer.x; }
	int getY() const { positionPlayer.y; }

	//�X�V���\�b�h
	int Update();

	//�`�惁�\�b�h
	void show();

	//ID�ɍ��킹���}�b�v�𐶐�����
	void createMap();
};