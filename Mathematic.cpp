#include <math.h>
#include "Mathematic.h"
#include "Player.h"
#include "Enemy.h"


#include "DxLib.h"

int damage(int attack_point, int diffence_point, int weak) {
	int x = attack_point / 100;
	int y = (attack_point * weak - diffence_point < 0) ? 0 : attack_point * weak - diffence_point;
	return x + 1 + y;
}

int move_range(int dex) {
	int t = dex / 50;
	return t + 3;
}