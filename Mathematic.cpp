#include <math.h>
#include "Mathematic.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "DxLib.h"


//ダメージの計算式
int damage(int attack_point, int diffence_point, int weak) {
	int x = attack_point / 100;
	int y = (attack_point * weak - diffence_point < 0) ? 0 : attack_point * weak - diffence_point;
	return x + 1 + y;
}

//移動範囲の計算式
int move_range(int dex) {
	int t = dex / 50;
	return t + 1;
}
