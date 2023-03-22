#pragma once
#include "archetype.h"

class paladin :public archetype {
	public:
		bool canCastSpells = true;
		std::vector<std::string> weaponsProficient;
		std::vector<std::string> armourProficient;
		std::vector<abilityScoresEnum> savesProficient = {WIS,CON};
		std::string className = "paladin";
};