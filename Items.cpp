#include "Items.h"
#include "IDs.h"

Item* search(int id) {
	switch (id) {
	case WOODSWORD:
		return new WoodSword();
		break;
	case LEATHERARM:
		return new LeatherArm();
		break;
	case LEATHERCAP:
		return new LeatherCap();
		break;
	case LEATHERCHEST:
		return new LeatherChest();
		break;
	case LEATHERSHIELD:
		return new LeatherSheild();
		break;
	case PORTION:
		return new Portion();
		break;
	}
}