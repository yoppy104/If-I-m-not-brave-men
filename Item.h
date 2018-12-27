#pragma once

class Item {
protected:
	char name[128];
	int id;			//id
	int price_buy;	//����
	int price_sell; //����
	bool is_sell;	//���p�\���ǂ���
	int image;		//�摜
	bool is_equip_weapon;	//����Ƃ��đ����\��
	bool is_equip_shield;	//���Ƃ��đ����\��
	bool is_equip_arm;		//����Ƃ��đ����\��
	bool is_equip_head;		//�������Ƃ��đ����\��
	bool is_equip_chest;	//���ɑ����\��

public:
	Item();
	Item(char name[], int id, int price, bool is_sell, int image, int is_equip);
	~Item();
	int getId();
	int getPriceBuy();
	int getPriceSell();
	bool getIsSell();
	void getName(int x, int y);
	int getImage();
	virtual bool effectBattle();
	virtual bool effectMap();
};