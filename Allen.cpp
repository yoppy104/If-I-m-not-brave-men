#include <string.h>
#include <math.h>
#include "Allen.h"
#include "Weapon.h"
#include "DxLib.h"
#include "Magics.h"
#include "IDs.h"

Allen::Allen(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon* _weapon, Armor* head, Armor* arm, Armor* chest, Armor* shield, int _image, int mp, int image_dead) :Player(name, x, y, hp, attack, diffence, magic_power, dex, _weapon, head, arm, chest, shield, _image, image_dead){
	this->mp = mp;
	this->mp_max = mp;
	this->setHasMp(true);
	this->id = ALLEN;
	LoadDivGraph("キャラチップ_アレン_正面.jpg", 2, 2, 1, 64, 64, this->image_map_front);
	LoadDivGraph("キャラチップ_アレン_背面1.jpg", 2, 2, 1, 64, 64, this->image_map_back);
	LoadDivGraph("キャラチップ_アレン_右.jpg", 4, 4, 1, 64, 64, this->image_map_right);
	LoadDivGraph("キャラチップ_アレン_左.jpg", 4, 4, 1, 64, 64, this->image_map_left);

	this->magics.push_back(new FireBall());
	this->magics.push_back(new Heal());
}

int Allen::getMp() {
	return this->mp;
}

int Allen::getMpMax() {
	return this->mp_max;
}

void Allen::plusMp(int point) {
	this->mp += point;
	if (this->mp > this->hp_max) {
		this->mp = this->hp_max;
	}
}

void Allen::plusMp() {
	this->mp = this->mp_max;
}

int Allen::sendEXp(int EXp) {
	allEXP += EXp;
	stuckEXP += EXp;
	bool can_LVUP = true;
	while (NextEXP <= stuckEXP)
	{
		stuckEXP -= NextEXP;
		NextEXP = NextEXP + 150 * pow(LV, 5.0 / 4.0);
		hp_max = hp_max + 2 * pow(LV, 0.25);
		attack = attack + pow(LV, 0.25);
		diffence = diffence + pow(LV, 0.25);
		mp = mp + pow(LV, 0.2);
		dex = dex + pow(LV, 0.2);
		LV++;
	}
	return 0;
}