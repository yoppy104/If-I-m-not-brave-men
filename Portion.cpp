#include "Portion.h"
#include "IDs.h"
#include "DxLib.h"

Portion::Portion() :Item("‰ñ•œ–ò", PORTION, 100, true, LoadGraph("fireball"), -1) {
	this->point = 20;
}

bool Portion::effectBattle() {
	return false;
}

bool Portion::effectMap() {

	return false;
}

void Portion::select(shared_ptr<PartyControl> pc) {
	shared_ptr<Player> temp;
	for (int i = 0; i < pc->getNumMember(); i++) {
		temp = pc->getMember(i);
		temp->getName(400, 100 + 100 * i, GetColor(0, 0, 0));
		DrawFormatString(600, 100 + 100 * i, GetColor(0, 0, 0), "%d/%d", temp->getHp(), temp->getHpMax());
	}
}