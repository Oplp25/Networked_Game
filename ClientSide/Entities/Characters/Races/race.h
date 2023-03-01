#pragma once
#include<vector>
#include "../abilityScoresEnum.h"

class race {
	private:
		std::vector<abilityScoresEnum> abilityScoreUpgrades;
	public:
		void applyAbiltyScoreIncreases(std::vector<int>& abilityScores);
};