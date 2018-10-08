#include "Character.h"
#include "Enemy.h"
#include "Character.h"
#include "Player.h"
#include "DxLib.h"
#include "draw.h"
#include <cstdlib>
#include <cmath>

using namespace std;

Enemy::Enemy(char name[], int x, int y, int hp, int attack, int diffence, int magic_power, int dex, int image) :Character(name, x, y, hp, attack, diffence, magic_power, dex){ // ‰Šú‰»
	this->image = image;
}

void Enemy::move(Player* p, Enemy* e, int background_image, stagedata stage) { // “G‚ÌˆÚ“®
	
}


int Enemy::getImage() {
	return this->image;
}