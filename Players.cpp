#include "DxLib.h"
#include "Player.h"
#include "Players.h"
#include "Weapon.h"
#include "Allen.h"
#include "Craig.h"
#include "Imitia.h"
#include "Rain.h"

int player_image = LoadGraph("プレイヤー.png"); // プレイヤーの画像
Weapon iron_sword(10, 50, 1, -1, 42); // 装備のクラス

Allen allen("allen", 100, 496 + 160 * 5, 136 + 160 * 5, 10, 2, iron_sword, player_image, 50, 5); // アレンの構造体定義
Rain rain("rain", 100, 496 + 160 * 5, 136 + 160 * 5, 10, 2, iron_sword, player_image, 50); // アレンの構造体定義
Craig craig("craig", 100, 496 + 160 * 5, 136 + 160 * 5, 10, 2, iron_sword, player_image, 50); // アレンの構造体定義
Imitia imitia("imitia", 100, 496 + 160 * 5, 136 + 160 * 5, 10, 2, iron_sword, player_image, 50); // アレンの構造体定義
Player players[4] = { allen, rain, craig, imitia };

