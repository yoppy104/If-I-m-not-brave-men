#include "NPC.h"
#include <string.h>
#include "DxLib.h"

NPC::NPC() {

}

NPC::NPC(char name[]) {
	strcpy(this->name, name);
}

void NPC::getName(int x, int y) {
	DrawFormatString(x, y, GetColor(0, 0, 0), this->name);
}

void NPC::chat() {

}