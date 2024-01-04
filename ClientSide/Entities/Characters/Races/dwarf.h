#pragma once
#include<vector>

#include "../abilityScoresEnum.h"
#include "race.h"

//child class of race
class dwarf:public race {
	public:
		std::string raceName = "Dwarf";
		std::vector<abilityScoresEnum> abilityScoreUpgrades = {CON,CON,STR};
		float speed = 2.5;
		int maxStaminaIncrease = 10;//dwarf will have a high stamina increase, haven't decided on a scale yet, so 10 is just a placeholder
};