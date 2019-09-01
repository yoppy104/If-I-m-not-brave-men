#include "PartyControll.h"
#include "DxLib.h"

PartyControll::PartyControll(std::vector <std::shared_ptr<Player>> players, int num, int coin) :
	member(players),
	numMagicStone(num),
	coin(coin)
{
	addItem(WOODSWORD, 1);
	addItem(LEATHERARM, 1);
	addItem(LEATHERCAP, 1);
	addItem(PORTION, 3);
	addItem(STEALLANCE, 1);
}

void PartyControll::delItem(int index) {
	items.erase(items.begin() + index);
}

//ID�Ɋ�Â����A�C�e���ǉ�
void PartyControll::addItem(ID id, int num){
	int i = 0;
	//���łɓ���ID�̃A�C�e�����������Ă�����A���𑝂₷�B
	for (i; i < items.size(); i++) {
		if (items[i].id == id) {
			items[i].num++;
			return;
		}
	}
	//�Ȃ�������A�V�����ǉ�����B
	items.push_back(ItemData{ id, std::make_shared<Item>(Item(id)), num });
}

//�|�C���^�Ɋ�Â����A�C�e���ǉ�
void PartyControll::addItem(item_ptr item, int num) {
	for (auto itr = items.begin(); itr != items.end(); itr++) {
		if (itr->id == item->getId()) {
			itr->num++;
			return;
		}
	}
	items.push_back(ItemData{ item->getId(), item, num });
}

//�A�C�e���̌������炷�B
void PartyControll::reduceItem(int index, int num) {
	if (items[index].num > num) {
		items[index].num -= num;
	}
	else {
		//����0�ȉ��ɂȂ�Ȃ�A���ڂ��̂��̂��폜����B
		delItem(index);
	}
}

void PartyControll::addNumMagicStone(int delta) {
	numMagicStone += delta;
}

void PartyControll::addNumCoin(int delta) {
	coin += delta;
}

//�v���C���[�ɑ���������B�܂��́A������ύX����
void PartyControll::setEquipment(int member_index, int item_index) {
	//���R�[�h��⊮
	/*
	int temp = items[item_index].instance->getIsEquip();
	if (temp == 1) {
		if (member[member_index]->hasEquip(1)) {
			addItem(member[member_index]->getWeaponId(), 1);
		}
		member[member_index]->setEquipment(items[item_index].instance->getId(), 1);
	}
	else {
		if (member[member_index]->hasEquip(temp)) {
			addItem(member[member_index]->getArmorId(temp), 1);
		}
		member[member_index]->setEquipment(items[item_index].instance->getId(), temp);
	}
	items[item_index].num--;
	if (items[item_index].num == 0) {
		items.erase(items.begin() + item_index);
	}
	*/

	//������A�N�Z�X���邽�ߕϐ��Ŋm��
	player_ptr target_member = member.at(member_index);
	//�������镔�ʂ�\���l���擾����
	int equipType = items[item_index].instance->getIsEquip();
	//�����ł��Ȃ��ꍇ�͂͂���
	if (equipType != 0) {
		//�������p�̃N���X�𑕔����Ă���ꍇ�́A�A�C�e�����X�g�ɒǉ����Ȃ�
		if (target_member->hasEquip(equipType)) {
			item_ptr old_equip_item = target_member->setEquipment(items.at(item_index).instance, equipType);
			addItem(old_equip_item, 1);
		}
		else {
			target_member->setEquipment(items.at(item_index).instance, equipType);
		}
		reduceItem(item_index, 1);
	}
}

void PartyControll::replaceEquipment(int member_index, int type) {
	//���R�[�h���ꉞ�c���Ă���
	/*
	switch (type) {
	case 1:
		if (member[member_index]->hasEquip(1)) {
			addItem(member[member_index]->getWeaponId(), 1);
		}
		member[member_index]->setEquipment(NOTEQUIPMENT, 1);
		break;
	case 2:
		if (member[member_index]->hasEquip(2)) {
			addItem(member[member_index]->getArmorId(2), 1);
		}
		member[member_index]->setEquipment(NOTEQUIPMENT, 2);
		break;
	case 3:
		if (member[member_index]->hasEquip(3)) {
			addItem(member[member_index]->getArmorId(3), 1);
		}
		member[member_index]->setEquipment(NOTEQUIPMENT, 3);
		break;
	case 4:
		if (member[member_index]->hasEquip(4)) {
			addItem(member[member_index]->getArmorId(4), 1);
		}
		member[member_index]->setEquipment(NOTEQUIPMENT, 4);
		break;
	case 5:
		if (member[member_index]->hasEquip(5)) {
			addItem(member[member_index]->getArmorId(5), 1);
		}
		member[member_index]->setEquipment(NOTEQUIPMENT, 5);
		break;
	}
	*/

	//������A�N�Z�X���邽�ߕϐ��Ŋm��
	player_ptr target_member = member.at(member_index);
	//���Ƃ��Ƒ������Ă����A�C�e��
	item_ptr old_equip_item = target_member->getEquipment(type);
	addItem(old_equip_item, 1);
	//�������p�̃A�C�e��������
	target_member->setEquipment(NOTEQUIPMENT, type);
}

//�}�b�v�ŃA�C�e�����g�p����
void PartyControll::useItemMap(int index) {
	items[index].instance->effectMap(member[0]);
	items[index].num--;
	if (items[index].num == 0) {
		items.erase(items.begin() + index);
	}
}

void PartyControll::GetItemName(int index, int x, int y) {
	items[index].instance->getName(x, y);
	DrawFormatString(x + 330, y, GetColor(0, 0, 0), "%d��", items[index].num);
}