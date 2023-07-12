#pragma once
#include "../item.h"
#include "weaponTemplates.h"
class weapon :item {
	public:
		int damage;
		float cooldown;
		int reach;
		int hands;
		weapon();
		weapon(std::string pname, int pcost, int pcharges, std::string pimagePath, int pdamage, float pcooldown, int preach, int phands);
		weapon(weaponTemplate stats);
	private:

};