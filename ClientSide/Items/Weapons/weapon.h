#pragma once
#include "../item.h"
#include "weaponTemplates.h"
class weapon :item {
	public:
		weapon();
		weapon(std::string name, int cost, int durability, std::string imagePath, int damage, float cooldown, int reach);
		weapon(weaponTemplate stats);
	private:

};