/*		if (select_do == 0) { //戦闘を行う場合

			int count_player = 0; //playerの行動回数
			int countthis->enemys = 0; //enemyの行動回数

			for (int step = 0; step < sizethis->enemys+size_players; step++) {
				//行動者を決定する

				if (count_deadthis->enemys == 3 || count_dead_players == 4) {
					break;
				}

				int side = -1; //どっちサイドか,0=player, 1=enemy, -1=NULL
				int person; //各サイドのどの人か
				if (countthis->enemys >= sizethis->enemys) {
					side = 0;
					person = count_player;
				}
				else if (count_player >= size_players) {
					side = 1;
					person = countthis->enemys;
				}
				else if (players[count_player]->getDex() >= enemy[countthis->enemys]->getDex()) {
					side = 0;
					person = count_player;
				}
				else {
					side = 1;
					person = countthis->enemys;
				}

				if (side == -1) { //例外処理。両方に行動可能なキャラがいなかったら、for文を終了させる.
					break;
				}

				//ここまで

				if (side == 0) { //味方サイドの行動
					count_player++;
					Player *me = players[person];

					if (me->getIsMoveable()) {
						select = 0; // 0:攻撃 1:いどう 2:アイテム 3:防御
						ClearDrawScreen();
						redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
						draw_command(select); //コマンド枠を描画

						int image = LoadGraph("battleframe.png");
						DrawGraph(me->getX(), me->getY(), image, TRUE);

						// 行動の選択
						bool infloop = true;
						while (infloop) {
							select = 0;
							while (CheckHitKey(KEY_INPUT_SPACE) == 0 && CheckHitKey(KEY_INPUT_B) == 0) { // spaceを押したら決定
								if (CheckHitKey(KEY_INPUT_DOWN)) { // 下を押したらselectを+1
									if (select <= 1) {
										select++;
										ClearDrawScreen();
										redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
										draw_command(select);
										PlaySoundMem(button_se, DX_PLAYTYPE_BACK, TRUE);
									}
									while (CheckHitKey(KEY_INPUT_DOWN)) {}
								}
								else if (CheckHitKey(KEY_INPUT_UP)) { // 上を押したらselectを―1
									if (select >= 1) {
										select--;
										ClearDrawScreen();
										redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
										draw_command(select);
										PlaySoundMem(button_se, DX_PLAYTYPE_BACK, TRUE);
									}
									while (CheckHitKey(KEY_INPUT_UP)) {}
								}
								else if (CheckHitKey(KEY_INPUT_ESCAPE)) {
									break;
								}
							}
							while (CheckHitKey(KEY_INPUT_B)) {
								if (step == 0) {
									PlaySoundMem(sound_cancel, DX_PLAYTYPE_BACK, TRUE);
								}
								select = -1;
							}
							while (CheckHitKey(KEY_INPUT_SPACE)) {}

							if (!CheckSoundMem(sound_cancel)) {
								PlaySoundMem(sound_define, DX_PLAYTYPE_BACK, TRUE);
							}

							if (CheckHitKey(KEY_INPUT_ESCAPE)) {
								break;
							}

							if (select == -1) {
								if (step == 0) {
									step = sizethis->enemys + size_players;
									infloop = false;
								}
							}
							else {
								infloop = false;
							}
						}

						redraw_battle(stage, enemy, sizethis->enemys, players, size_players);

						if (select == 0) { //通常攻撃
							int point = draw_attackable_area(me, players, size_players, enemy, sizethis->enemys, 0);
							draw_attack_area(point, me);
							bool is_attack = true;
							while (CheckHitKey(KEY_INPUT_SPACE) == 0 || (496 + 160 * (point % 10) == me->getX() && 136 + 160 * (int)(point / 10) == me->getY())) {
								if (CheckHitKey(KEY_INPUT_RIGHT)) {
									if ((point % 10) + 1 < 6) {
										if (me->is_attackable(point + 1)) {
											point += 1;
											ClearDrawScreen();
											redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
											draw_attackable_area(me, players, size_players, enemy, sizethis->enemys, 0);
											draw_attack_area(point, me);
										}
									}
									while (CheckHitKey(KEY_INPUT_RIGHT)) {}
								}
								else if (CheckHitKey(KEY_INPUT_LEFT)) {
									if ((point % 10) - 1 >= 0) {
										if (me->is_attackable(point - 1)) {
											point -= 1;
											ClearDrawScreen();
											redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
											draw_attackable_area(me, players, size_players, enemy, sizethis->enemys, 0);
											draw_attack_area(point, me);
										}
									}
									while (CheckHitKey(KEY_INPUT_LEFT)) {}
								}
								else if (CheckHitKey(KEY_INPUT_UP)) {
									if ((point / 10) - 1 >= 0) {
										if (me->is_attackable(point - 10)) {
											point -= 10;
											ClearDrawScreen();
											redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
											draw_attackable_area(me, players, size_players, enemy, sizethis->enemys, 0);
											draw_attack_area(point, me);
										}
									}
									while (CheckHitKey(KEY_INPUT_UP)) {}
								}
								else if (CheckHitKey(KEY_INPUT_DOWN)) {
									if ((point / 10) + 1 < 6) {
										if (me->is_attackable(point + 10)) {
											point += 10;
											ClearDrawScreen();
											redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
											draw_attackable_area(me, players, size_players, enemy, sizethis->enemys, 0);
											draw_attack_area(point, me);
										}
									}
									while (CheckHitKey(KEY_INPUT_DOWN)) {}
								}
								else if (CheckHitKey(KEY_INPUT_B)) {

									PlaySoundMem(sound_cancel, DX_PLAYTYPE_BACK, TRUE);
									is_attack = false;
									step--;
									count_player--;
									break;
								}
								else if (CheckHitKey(KEY_INPUT_ESCAPE)) {
									break;
								}
							}
							while (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_B)) {}

							if (!CheckSoundMem(sound_cancel)) {
								PlaySoundMem(sound_define, DX_PLAYTYPE_BACK, TRUE);
							}

							if (CheckHitKey(KEY_INPUT_ESCAPE)) {
								break;
							}

							if (is_attack) {
								PlaySoundMem(me->getWeapon().getSound(), DX_PLAYTYPE_BACK, TRUE);
								for (int frame = 0; frame < 4; frame++) {
									ClearDrawScreen();
									redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
									draw_attack_animation((int)(point % 10) * 160 + 496, (int)(point / 10) * 160 + 136, me->getX(), me->getY(), person, frame);
									WaitTimer(5);
								}
								me->battle(point, players, size_players, enemy, sizethis->enemys);
							}

							for (int i = 0; i < size_players; i++) {
								if (players[i]->getIsMoveable()) {
									if (players[i]->getHp() <= 0) {
										players[i]->down();
										count_dead_players++;
									}
								}
							}
							for (int i = 0; i < sizethis->enemys; i++) {
								if (enemy[i]->getIsMoveable()) {
									if (enemy[i]->getHp() <= 0) {
										enemy[i]->down();
										count_deadthis->enemys++;
									}
								}
							}
						}
						else if (select == 1) { //移動

							int movelimit = me->getDex();

							SetFontSize(48); // フォントサイズの指定
							DrawFormatString(1500, 1000, GetColor(255, 255, 255), "残り%d歩\nSPACEで移動終了", movelimit);
							SetFontSize(32);

							int is_key = -1; // 0:right, 1:left, 2:up, 3:down

							int prot_x = me->getX();
							int prot_y = me->getY();

							while (movelimit > 0 && CheckHitKey(KEY_INPUT_SPACE) == 0) {

								if (CheckHitKey(KEY_INPUT_UP)) {
									if (me->move(0, -160, stage, enemy, sizethis->enemys, players, size_players)) {
										if (!CheckSoundMem(walk_se)) {
											PlaySoundMem(walk_se, DX_PLAYTYPE_BACK, FALSE);
										}
										if (is_key == 3){
											movelimit++;
											is_key = -1;
										}
										else {
											movelimit--;
											is_key = 2;
										}
										ClearDrawScreen();
										redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
										SetFontSize(48); // フォントサイズの指定
										DrawFormatString(1500, 1000, GetColor(255, 255, 255), "残り%d歩\nSPACEで移動終了", movelimit);
										SetFontSize(32);
									}
									while (CheckHitKey(KEY_INPUT_UP)) {}
								}
								else if (CheckHitKey(KEY_INPUT_DOWN)) {
									if (me->move(0, 160, stage, enemy, sizethis->enemys, players, size_players)) {
										if (!CheckSoundMem(walk_se)) {
											PlaySoundMem(walk_se, DX_PLAYTYPE_BACK, FALSE);
										}
										if (is_key == 2) {
											movelimit++;
											is_key = -1;
										}
										else {
											movelimit--;
											is_key = 3;
										}
										ClearDrawScreen();
										redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
										SetFontSize(48); // フォントサイズの指定
										DrawFormatString(1500, 1000, GetColor(255, 255, 255), "残り%d歩\nSPACEで移動終了", movelimit);
										SetFontSize(32);
									}
									while (CheckHitKey(KEY_INPUT_DOWN)) {}
								}
								else if (CheckHitKey(KEY_INPUT_RIGHT)) {
									if (me->move(160, 0, stage, enemy, sizethis->enemys, players, size_players)) {
										if (!CheckSoundMem(walk_se)) {
											PlaySoundMem(walk_se, DX_PLAYTYPE_BACK, FALSE);
										}
										if (is_key == 1) {
											movelimit++;
											is_key = -1;
										}
										else {
											movelimit--;
											is_key = 0;
										}
										ClearDrawScreen();
										redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
										SetFontSize(48); // フォントサイズの指定
										DrawFormatString(1500, 1000, GetColor(255, 255, 255), "残り%d歩\nSPACEで移動終了", movelimit);
										SetFontSize(32);
									}
									while (CheckHitKey(KEY_INPUT_RIGHT)) {}
								}
								else if (CheckHitKey(KEY_INPUT_LEFT)) {
									if (me->move(-160, 0, stage, enemy, sizethis->enemys, players, size_players)) {
										if (!CheckSoundMem(walk_se)) {
											PlaySoundMem(walk_se, DX_PLAYTYPE_BACK, FALSE);
										}
										if (is_key == 0) {
											movelimit++;
											is_key = -1;
										}
										else {
											movelimit--;
											is_key = 1;
										}
										ClearDrawScreen();
										redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
										SetFontSize(48); // フォントサイズの指定
										DrawFormatString(1500, 1000, GetColor(255, 255, 255), "残り%d歩\nSPACEで移動終了", movelimit);
										SetFontSize(32);
									}
									while (CheckHitKey(KEY_INPUT_LEFT)) {}
								}
								else if (CheckHitKey(KEY_INPUT_B)) {
									PlaySoundMem(sound_cancel, DX_PLAYTYPE_NORMAL, TRUE);
									me->setX(prot_x);
									me->setY(prot_y);
									step--;
									count_player--;
									break;
								}
								else if (CheckHitKey(KEY_INPUT_ESCAPE)) {
									break;
								}
							}
							while (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_B)) {}

							if (!CheckSoundMem(sound_cancel)) {
								PlaySoundMem(sound_define, DX_PLAYTYPE_BACK, TRUE);
							}

							if (CheckHitKey(KEY_INPUT_ESCAPE)) {
								break;
							}
							StopSoundMem(walk_se);
						}
						else if (select == 2) { //魔術行使の場合
							bool loop = true;
							while (loop && CheckHitKey(KEY_INPUT_B) == 0) {
								int select_magic = 0;
								int page = 1;
								showMagic(me, page);
								draw_magic_select(select_magic);
								WaitTimer(200);

								while (!CheckHitKey(KEY_INPUT_SPACE)) {
									
									if (CheckHitKey(KEY_INPUT_RIGHT)) {

									}
									else if (CheckHitKey(KEY_INPUT_LEFT)) {

									}
									else if (CheckHitKey(KEY_INPUT_UP)) { //上キー
										if (select_magic - 1 >= 0) {
											select_magic--;

											showMagic(me, page);
											draw_magic_select(select_magic);
										}
									}
									else if (CheckHitKey(KEY_INPUT_DOWN)) { //下キー
										if (select_magic + 1 < 2) {
											select_magic++;
											showMagic(me, page);
											draw_magic_select(select_magic);
										}
									}
									
									if (CheckHitKey(KEY_INPUT_B)) {
										PlaySoundMem(sound_cancel, DX_PLAYTYPE_NORMAL, TRUE);
										step--;
										select_magic = -1000;
										count_player--;
										loop = false;
										break;
									}
									else if (CheckHitKey(KEY_INPUT_ESCAPE)) {
										break;
									}
									while (CheckHitKey(KEY_INPUT_DOWN) ||
										CheckHitKey(KEY_INPUT_UP) ||
										CheckHitKey(KEY_INPUT_RIGHT) ||
										CheckHitKey(KEY_INPUT_LEFT)) {
									}
								}
								while (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_B)) {

								}

								PlaySoundMem(sound_define, DX_PLAYTYPE_BACK, TRUE);

								if (CheckHitKey(KEY_INPUT_ESCAPE)) {
									break;
								}

								if (select_magic >= 0) {
									if (me->getMagics() & (int)pow(2, select_magic)) {
										
										int cost;
										if (select_magic == 0) {
											cost = FireBall().getCost();
										}
										else {
											cost = Heal().getCost();
										}
											
										if (me->getHasMp()) {
											if (me->getMp() >= cost) {
												if (useMagic(select_magic, 0, stage, players, person, size_players, enemy, sizethis->enemys)) {
													PlaySoundMem(sound_cancel, DX_PLAYTYPE_BACK, TRUE);
													step--;
													count_player--;
													while (CheckHitKey(KEY_INPUT_B)) {}
													break;
												}
												else {
													me->plusMp(-cost);
													loop = false;
													for (int i = 0; i < size_players; i++) {
														if (players[i]->getIsMoveable()) {
															if (players[i]->getHp() <= 0) {
																players[i]->down();
																count_dead_players++;
															}
														}
													}
													for (int i = 0; i < sizethis->enemys; i++) {
														if (enemy[i]->getIsMoveable()) {
															if (enemy[i]->getHp() <= 0) {
																enemy[i]->down();
																count_deadthis->enemys++;
															}
														}
													}
												}
											}
											else {
												PlaySoundMem(sound_cancel, DX_PLAYTYPE_BACK, TRUE);
												DrawFormatString(800, 300, GetColor(0, 0, 0), "MPが足りません");
											}
										}
										else {
											if (me->getMagicStone() >= cost) {
												if (useMagic(select_magic, 0, stage, players, person, size_players, enemy, sizethis->enemys)) {
													PlaySoundMem(sound_cancel, DX_PLAYTYPE_BACK, TRUE);
													step--;
													count_player--;
													while (CheckHitKey(KEY_INPUT_B)) {}
													break;
												}
												else {
													me->plusMagicStone(-cost);
													loop = false;
													for (int i = 0; i < size_players; i++) {
														if (players[i]->getIsMoveable()) {
															if (players[i]->getHp() <= 0) {
																players[i]->down();
																count_dead_players++;
															}
														}
													}
													for (int i = 0; i < sizethis->enemys; i++) {
														if (enemy[i]->getIsMoveable()) {
															if (enemy[i]->getHp() <= 0) {
																enemy[i]->down();
																count_deadthis->enemys++;
															}
														}
													}
												}
											}
											else {
												PlaySoundMem(sound_cancel, DX_PLAYTYPE_BACK, TRUE);
												DrawFormatString(800, 600, GetColor(0, 0, 0), "MPが足りません");
												WaitTimer(500);
											}
										}										
									}
								}

							}
						}
					}
				}
				else if (side == 1) {
					redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
					Enemy* now = enemy[countthis->enemys];

					countthis->enemys++;

					if (now->getIsMoveable()) {
						int attackpoint_x = 0;
						int attackpoint_y = 0;
						for (int i = 0; i < size_players; i++) {
							if (now->getX() - 160 == players[i]->getX() || now->getX() == players[i]->getX() || now->getX() + 160 == players[i]->getX()) {
								if (now->getY() - 160 == players[i]->getY() || now->getY() == players[i]->getY() || now->getY() + 160 == players[i]->getY()) {
									if (players[i]->getIsMoveable()) {
										if (attackpoint_x == 0 && attackpoint_y == 0) {
											attackpoint_x = players[i]->getX() - now->getX();
											attackpoint_y = players[i]->getY() - now->getY();
										}
										else {
											if (GetRand(1) % 2 == 0) {
												attackpoint_x = players[i]->getX() - now->getX();
												attackpoint_y = players[i]->getY() - now->getY();
											}
										}
									}
								}
							}
						}

						if (attackpoint_x == 0 && attackpoint_y == 0) {
							int move_limit = move_range(now->getDex());
							int dx, dy;

							int move_select[4][4] = { {160, 0}, {0, -160}, {-160, 0},  {0, 160} };
							int count;
							int index;
							while (move_limit > 0) {
								/*
								SRand(time(NULL));
								dx = 0;
								dy = 0;
								if (GetRand(1) % 2 == 0) {
									dx = (GetRand(2) - 1) * 160;
								}
								else {
									dy = (GetRand(2) - 1) * 160;
								}

								if (!CheckSoundMem(move_slime_se)) {
									PlaySoundMem(move_slime_se, DX_PLAYTYPE_BACK, TRUE);
								}
								
								SRand(time(NULL));

								count = 3;
								index = GetRand(3);
								while (count > 0) {
									dx = move_select[index][0];
									dy = move_select[index][1];
									if (now->move(dx, dy, players, size_players, enemy, sizethis->enemys, stage)) {
										move_limit--;
										break;
									}
									count--;
									index = (index + 1) % 4;
								}
								if (count == 0) {
									break;
								}

							}
						}
						else {
							int prot_x = now->getX();
							int prot_y = now->getY();
							for (int i = 0; i < 4; i++) {
								ClearDrawScreen();
								if (i < 2) {
									now->setX(now->getX() + attackpoint_x / 4);
									now->setY(now->getY() + attackpoint_y / 4 - 40);
								}
								else {
									now->setX(now->getX() + attackpoint_x / 4);
									now->setY(now->getY() + attackpoint_y / 4 + 40);
								}
								redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
								WaitTimer(5);
							}
							PlaySoundMem(attack_slime_se, DX_PLAYTYPE_BACK, TRUE);
							ClearDrawScreen();
							now->setX(prot_x);
							now->setY(prot_y);
							redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
							now->battle(attackpoint_x, attackpoint_y, players, size_players);
							for (int i = 0; i < size_players; i++) {
								if (players[i]->getIsMoveable()) {
									if (players[i]->getHp() <= 0) {
										players[i]->down();
										count_dead_players++;
									}
								}
							}
							for (int i = 0; i < sizethis->enemys; i++) {
								if (enemy[i]->getIsMoveable()) {
									if (enemy[i]->getHp() <= 0) {
										enemy[i]->down();
										count_deadthis->enemys++;
									}
								}
							}
						}
						WaitTimer(300);
					}
				}
			}
		}
		else if (select_do == 1) { //逃げる場合
			if (GetRand(100) < 50) {
				//DrawFormatString(100, 100, GetColor(0, 0, 0), "run");
				//WaitTimer(150);
				//is_loop = false;
			}
			else {
				//DrawFormatString(100, 100, GetColor(0, 0, 0), "don't run");
				//WaitTimer(150);
			}
		}
	}

	if (!CheckHitKey(KEY_INPUT_ESCAPE)) {
		redraw_battle(stage, enemy, sizethis->enemys, players, size_players);
		WaitTimer(400);
		StopSoundMem(main_bgm);
		if (count_deadthis->enemys == 3) {
			int win_bgm = LoadSoundMem("win(test).wav");
			PlaySoundMem(win_bgm, DX_PLAYTYPE_LOOPBIT, TRUE);
			ClearDrawScreen();
			int image = LoadGraph("ゲームクリア画面.png");
			//DrawFormatString(960, 600, GetColor(255, 255, 255), "GameClear");
			DrawGraph(0, 0, image, TRUE);
			WaitKey();
			StopSoundMem(win_bgm);
		}
		else if (count_dead_players == 4 {
			int lose_bgm = LoadSoundMem("lose(test).wav");
			PlaySoundMem(lose_bgm, DX_PLAYTYPE_LOOPBIT, TRUE);
			ClearDrawScreen();
			int image = LoadGraph("ゲームオーバー画面.png");
			DrawFormatString(960, 600, GetColor(255, 255, 255), "GameOver");
			DrawGraph(0, 0, image, TRUE);
			WaitKey();
			StopSoundMem(lose_bgm);
		}
	
}
*/

#include "Battle.h"
#include "DxLib.h"
#include "draw.h"
#include "IDs.h"

Battle::Battle() {

}

Battle::Battle(vector <Player*> player) {
	int enemy_image = LoadGraph("スライム.png"); // 敵の画像
	int enemy_image_dead = LoadGraph("スライムdead.png");
	Enemy* enemy_a = new Enemy("スライムA", 496 + 160 * 0, 136 + 160 * 0, 20, 10, 13, 2, 4, enemy_image, enemy_image_dead); // スライムの構造体定義
	Enemy* enemy_b = new Enemy("スライムB", 496 + 160 * 2, 136 + 160 * 0, 22, 11, 10, 2, 4, enemy_image, enemy_image_dead); // スライムの構造体定義
	Enemy* enemy_c = new Enemy("スライムC", 496 + 160 * 4, 136 + 160 * 0, 25, 13, 8, 2, 4, enemy_image, enemy_image_dead); // スライムの構造体定義
	this->enemys = { enemy_a, enemy_b, enemy_c };
	for (int i = 1; i < enemys.size(); i++) {
		int j = i;
		while (j > 0 && enemys[j]->getDex() > enemys[j - 1]->getDex()) {
			Enemy* t = enemys[j - 1];
			enemys[j - 1] = enemys[j];
			enemys[j] = t;
		}
	}
	this->players = player;
	this->stage = 0b1111111111111111111111111111111111111;
	this->select = 0;
	this->next_player = 0;
	this->next_enemy = 0;
	if (players[0]->getDex() < enemys[0]->getDex()) {
		this->turn_character = enemys[0];
		this->next_enemy++;
	}
	else {
		this->turn_character = players[0];
		this->next_player++;
	}

	//画像のロード
	this->command_image = LoadGraph("command.png"); // コマンドパネル
	this->point_image = LoadGraph("pointer.png"); // コマンド選択用のポインタ画像
	this->playerpanel_image_blue = LoadGraph("playerdata_blue.png");
	this->playerpanel_image_red = LoadGraph("playerdata_red.png");
	this->playerpanel_image_gray = LoadGraph("playerdata_gray.png");
	this->background = LoadGraph("戦闘背景_草原.jpg"); // 背景画像
}

Battle::~Battle() {
	for (int i = 0; i < this->enemys.size(); i++) {
		delete this->enemys[i];
	}
	DeleteGraph(this->command_image);
	DeleteGraph(this->point_image);
}

void Battle::draw_command() {
	DrawRotaGraph(200, 400, 2.0, 0, this->command_image, TRUE); //コマンドフレームの描画
	DrawRotaGraph(120, 220 + 100 * this->select, 1.5, 0, this->point_image, TRUE); // 選択用ポインタの描画
	DrawFormatString(150, 200, GetColor(0, 0, 0), "たたかう");
	DrawFormatString(150, 300, GetColor(0, 0, 0), "いどう");
	DrawFormatString(150, 400, GetColor(0, 0, 0), "魔術");
}

void Battle::draw_command_do() {
	DrawRotaGraph(200, 400, 2.0, 0, this->command_image, TRUE); //コマンドフレームの描画
	DrawRotaGraph(120, 220 + 200 * this->select, 1.5, 0, this->point_image, TRUE); // 選択用ポインタの描画
	DrawFormatString(150, 200, GetColor(0, 0, 0), "せんとう");
	DrawFormatString(150, 400, GetColor(0, 0, 0), "とうそう");
}

Enemy* Battle::getEnemy(int index) {
	return enemys[index];
}

vector <Enemy*> Battle::getEnemys() {
	return enemys;
}

int Battle::getNumEnemys() {
	return enemys.size();
}

int Battle::getSelect() {
	return this->select;
}

void Battle::minusSelect() {
	this->select--;
}

void Battle::plusSelect() {
	this->select++;
}

void Battle::Update(int mode) {
	DrawGraph(0, 0, this->background, TRUE);
	battle_stage(stage);
	for (int i = 0; i < this->enemys.size(); i++) {
		if (this->enemys[i]->getIsMoveable()) {
			DrawGraph(this->enemys[i]->getX(), this->enemys[i]->getY(), this->enemys[i]->getImage(), TRUE);
		}
		else {
			DrawGraph(this->enemys[i]->getX(), this->enemys[i]->getY(), this->enemys[i]->getImageDead(), TRUE);
		}
	}

	for (int i = 0; i < this->players.size(); i++) {
		if (this->players[i]->getIsMoveable()) {
			DrawGraph(this->players[i]->getX(), this->players[i]->getY(), this->players[i]->getImage(), TRUE);
			if ((this->players[i]->getHp() / this->players[i]->getHpMax()) > 0.2) {
				draw_param(1500, 100 + 150 * i, this->players[i], this->playerpanel_image_blue);
			}
			else {
				draw_param(1500, 100 + 150 * i, this->players[i], this->playerpanel_image_red);
			}
		}
		else {
			DrawGraph(this->players[i]->getX(), this->players[i]->getY(), this->players[i]->getImageDead(), TRUE);
			draw_param(1500, 100 + 150 * i, this->players[i], this->playerpanel_image_gray);
		}
	}
	if (mode == BATTLE_DO_SELECT) {
		this->draw_command_do();
	}
	else if (mode = BATTLE_DO_PLAYER) {
		this->draw_command();
	}
}

void Battle::changeNextCharacter() {
	if (this->next_enemy + this->next_player > this->players.size() + this->enemys.size()) {
		this->next_enemy = 0;
		this->next_player = 0;
	}
	if (this->enemys[this->next_enemy]->getDex() > this->players[this->next_player]->getDex()) {
		this->turn_character = this->enemys[this->next_enemy];
		this->next_enemy++;
	}
	else {
		this->turn_character = this->players[this->next_player];
		this->next_player++;
	}
}

void Battle::select_init_() {
	this->select = 0;
}

int Battle::select_do_player() {
	this->select_init_();
	if (this->select == 0) {
		this->draw_command();
		return 0;
	}
	else if (this->select == 1) {
		if (GetRand(100) < 50) {
			DrawFormatString(100, 100, GetColor(0, 0, 0), "run");
			return 1;
		}
		else {
			DrawFormatString(100, 100, GetColor(0, 0, 0), "don't run");
			return 2;
		}
	}
}