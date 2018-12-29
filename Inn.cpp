#include "Inn.h"
#include "DxLib.h"
#include "M_Functions.h"

Inn::Inn(int pos_x, int pos_y, char name[], vector <char*> text, int price, PartyControl* pc) : NPC (pos_x, pos_y, name, text){
	this->price = price;
	this->pc = pc;
	this->select_main = false;
	this->subwindow_image = LoadGraph("command.png");
}

bool Inn::chat() {
	DrawExtendGraph(100, 800, 1860, 1000, this->text_box, TRUE);
	this->getName(150, 810);
	if (this->step == 1) {
		DrawFormatString(150, 850, GetColor(255, 255, 255), this->text[this->step],this->price * pc->getNumMember());
		DrawExtendGraph(1600, 700, 1800, 800, this->subwindow_image, TRUE);
		DrawFormatString(1650, 735, GetColor(0, 0, 0), "‚Í‚¢");
		DrawFormatString(1650, 765, GetColor(0, 0, 0), "‚¢‚¢‚¦");
		DrawLine(1645, 740 + 30 * this->select_main, 1750, 740 + 30 * this->select_main, GetColor(0, 0, 0), 5);
		if (Button(KEY_INPUT_UP) == 1) {

		}
		else if (Button(KEY_INPUT_DOWN) == 1) {

		}
		else if (Button(KEY_INPUT_SPACE) == 1) {

		}
		else if (Button(KEY_INPUT_B) == 1) {

		}
	}
	else {
		DrawFormatString(150, 850, GetColor(255, 255, 255), this->text[this->step]);
		if (Button(KEY_INPUT_SPACE) == 1) {
			if (this->step == this->text.size() - 1) {
				this->step = 0;
				return true;
			}
			this->step++;
		}
	}
	return false;
}