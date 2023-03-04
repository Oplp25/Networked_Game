#pragma once
#include<vector>
#include "../abilityScoresEnum.h"

class race {
	private:
	public:
		std::vector<abilityScoresEnum> abilityScoreUpgrades;
		int maxManaIncrease = 0;
		int maxHealthIncrease = 0;
		int maxStaminaIncrease = 0;
		int speed;
		//resistances/weaknesses
};