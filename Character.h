#pragma once
#include "Weapon.h"
#include <string>

using namespace std; 

// �L�����N�^�[���`����N���X
class Character {
protected:
	string name; // ���O�B����Ō̂��Ǘ�����
	int x; //�`�掞��x���W
	int y; //�`�掞��y���W
	int hp; //���ݑ̗�
	int hp_max; //�ő�̗�
	int attack; //�U����
	int diffence; //�h���
	int magic_power; //����
	int dex; //�q����
	bool has_mp; //MP�̃X�e�[�^�X�������Ă��邩
	int image;
	int image_dead;
	bool is_moveable;

	int image_map_front[2];	//map�ł̐��ʉ摜
	int image_map_back[2];	//map�ł̔w�ʉ摜
	int image_map_right[4];	//map�ł̉E���摜
	int image_map_left[4];	//map�ł̍����摜
public:
	Character();
	Character(string name, int x, int y, int hp, int attack, int diffence, int magic_power, int dex, int image, int image_dead);
	Character(int xpos, int ypos);
	void getName(int x, int y, int col);
	int getX();
	void setX(int dx);
	int getY();
	void setY(int dy);
	int getHp();
	int getHpMax();
	void plusHp(int point);
	virtual int getAttack();
	virtual int getDiffence();
	int getMagicPower();
	int getDex();
	bool getHasMp();
	void setHasMp(bool);
	int getImage();
	int getImageDead();
	void down();
	void alive();
	int getIsMoveable();

	//Allen�p
	virtual int getMp();

	//player�p
	virtual void move();
	virtual void battle();
	virtual bool is_attackable();
	virtual Weapon* getWeapon();
};