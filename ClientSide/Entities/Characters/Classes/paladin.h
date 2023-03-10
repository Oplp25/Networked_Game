#pragma once
#include "archetype.h"

class paladin :archetype {
	protected:
		bool canCastSpells = true;
		std::vector<std::string> weaponsProficient;
		std::vector<std::string> armourProficient;
		std::vector<abilityScoresEnum> savesProficient = {WIS,CON};
	public:
		std::string className = "paladin";
};