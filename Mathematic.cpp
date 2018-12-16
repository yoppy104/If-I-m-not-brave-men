#include <math.h>
#include "Mathematic.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "DxLib.h"

using namespace std;

int damage(int attack_point, int diffence_point, int weak) {
	int x = attack_point / 100;
	int y = (attack_point * weak - diffence_point < 0) ? 0 : attack_point * weak - diffence_point;
	return x + 1 + y;
}

int move_range(int dex) {
	int t = dex / 50;
	return t + 3;
}
/*
void createMap() {
	ifstream stream("world_map.csv");
	string line;
	int data[5][5];
	const string delim = ",";

	int row = 0;
	int col;
	while (getline(stream, line)) {
		col = 0;
		for (string::size_type spos, epos = 0;
			(spos = line.find_first_not_of(delim, epos)) != string::npos;) {
			string token = line.substr(spos, (epos = line.find_first_of(delim, spos)) - spos);
			data[row][col++] = stoi(token);
		}
		++row;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int image;
			if (data[i][j] == 0) {
				image = LoadGraph("battlepanel.png");
			}
			else if (data[i][j] == 1) {
				image = LoadGraph("attackpanel.png");
			}
			DrawGraph(100 + 160 * i, 100 + 160 * j, image, TRUE);
		}
	}

	WaitKey();
}
*/