#include "Magics.h"
#include "IDs.h"

Magic* searchMagic(int id) {
	switch (id) {
	case FIREBALL:
		return new FireBall();
		break;
	case HEAL:
		return new Heal();
		break;
	}
}