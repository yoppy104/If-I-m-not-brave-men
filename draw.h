#pragma once

#include <iostream>
#include <math.h>
#include "Enemy.h"
#include "Player.h"
#include "DxLib.h"

typedef unsigned long long stagedata;

void battle_stage(stagedata stage);

void redraw_battle(stagedata stage, Enemy *_enemy, Player *_player);

void draw_command(int sele);

int draw_attackable_area(Player me, Enemy enemy);

void draw_attack_area(int point, Player me);