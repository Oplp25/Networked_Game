#pragma once
#include<vector>
#include "../abilityScoresEnum.h"

class race {
	public:
		std::vector<abilityScoresEnum> abilityScoreUpgrades;
		int maxManaIncrease = 0;
		int maxHealthIncrease = 0;
		int maxStaminaIncrease = 0;
		int speed;
		std::string raceName;
		//resistances/weaknesses
};