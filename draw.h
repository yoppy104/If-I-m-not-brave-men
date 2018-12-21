#pragma once

#include <iostream>
#include <math.h>
#include "Enemy.h"
#include "Player.h"
#include "DxLib.h"

typedef unsigned long long stagedata;

void battle_stage(stagedata stage);

void draw_param(int x, int y, Player* player, int image);

void redraw_battle(stagedata stage, Enemy **_enemy, int size_enemy, Player **_player, int size_player);

void draw_command(int sele);

void draw_command_do(int sele);

int draw_attackable_area(Player* me, Player** players, int size_players, Enemy** enemy, int size_enemy, int is_weapon);

void draw_attack_area(int point, Player* me, int is_magic = 0);

void draw_magic_select(int select);

void draw_attack_animation(int attack_x, int attack_y, int pos_x, int pos_y, int type, int frame);