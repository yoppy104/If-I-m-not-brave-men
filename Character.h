#pragma once

// �L�����N�^�[���`����N���X
class Character {
private:
	char name[15]; // ���O�B����Ō̂��Ǘ�����
	int x; //�`�掞��x���W
	int y; //�`�掞��y���W
	int hp; //���ݑ̗�
	int hp_max; //�ő�̗�
	int attack; //�U����
	int diffence; //�h���
	int magic_power; //����
	int dex; //�q����
public:
	Character();
	Character(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex);
	void getName(int x, int y);
	int getX();
	void setX(int dx);
	int getY();
	void setY(int dy);
	int getHp();
	int getHpMax();
	void plusHp(int point);
	int getAttack();
	int getDiffence();
	int getMagicPower();
	int getDex();
};