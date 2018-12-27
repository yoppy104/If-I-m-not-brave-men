#include <string.h>
#include "Allen.h"
#include "Weapon.h"
#include "DxLib.h"
#include "FireBall.h"

Allen::Allen(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, Weapon _weapon, int _image, int mp, int image_dead) :Player(name, x, y, hp, attack, diffence, magic_power, dex, _weapon, _image, image_dead){
	this->mp = mp;
	this->setHasMp(true);
	LoadDivGraph("キャラチップ_アレン_正面.jpg", 2, 2, 1, 64, 64, this->image_map_front);
	LoadDivGraph("キャラチップ_アレン_背面1.jpg", 2, 2, 1, 64, 64, this->image_map_back);
	LoadDivGraph("キャラチップ_アレン_右.jpg", 4, 4, 1, 64, 64, this->image_map_right);
	LoadDivGraph("キャラチップ_アレン_左.jpg", 4, 4, 1, 64, 64, this->image_map_left);

	this->magics.push_back(FireBall());
}

int Allen::getMp() {
	return this->mp;
}

void Allen::plusMp(int point) {
	this->mp += point;
}