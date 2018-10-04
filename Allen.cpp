#include <string.h>
#include "Allen.h"
#include "Weapon.h"

Allen::Allen(char _name[], int _hp, int _x, int _y, int _attack, int _diffence, Weapon _weapon, int _image, int dex, int mp) :Player(_name, _hp, _x, _y, _attack, _diffence, _weapon, _image, dex){
	this->mp = mp;
}