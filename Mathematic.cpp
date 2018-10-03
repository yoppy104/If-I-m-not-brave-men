#include <math.h>
#include "Mathematic.h"

int damage(int attack_point, int diffence_point, int weak) {
	return ceil(attack_point / 100) + ((attack_point * weak - diffence_point < 0) ? 0 : attack_point * weak - diffence_point);
}