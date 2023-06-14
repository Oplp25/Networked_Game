#pragma once
#include<vector>
#include "../abilityScoresEnum.h"

class race {
	public:
		std::vector<abilityScoresEnum> abilityScoreUpgrades;
		int maxManaIncrease = 0;
		int maxHealthIncrease = 0;
		int maxStaminaIncrease = 0;
		float speed = 30;
		std::string raceName;
		//resistances/weaknesses
};