#include "WoodSword.h"

WoodSword::WoodSword() :Weapon("�ؓ�", WOODSWORD, true, 5, 100, 1, 0, 0) {
	//sound �� image �� NULL �ɂȂ��Ă���
}

bool WoodSword::effectBattle() {
	return false;
}

bool WoodSword::effectMap() {
	return false;
}

void WoodSword::selectAttack() {

}

void WoodSword::drawAnimation() {

}

void WoodSword::drawAttackableArea() {

}