#pragma once
#include<vector>

#include "../abilityScoresEnum.h"
#include "race.h"
class dwarf :race {
	public:
		std::vector<abilityScoresEnum> abilityScoreUpgrades = {CON,CON,STR};
		int speed = 25;//speed in DnD feet, will need to convert to my own system
		int maxStaminaIncrease = 10;//dwarf will have a high stamina increase, haven't decided on a scale yet, so 10 is just a placeholder
};