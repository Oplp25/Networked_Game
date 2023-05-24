#pragma once
#include "archetype.h"
#include<iostream>

class paladin :public archetype {
	public:
		int getHitDiceType() override;
		std::string getClassName() override;
		bool getCanCastSpells() override;
		std::vector<abilityScoresEnum> getSavesProficient() override;
		std::vector<std::string> getArmourProficient() override;
		std::vector<std::string> getWeaponsProficient() override;
		bool canCastSpells = true;
		std::vector<abilityScoresEnum> savesProficient = { WIS,CON };
		std::string className = "paladin";
		int hitDiceType = 10;
		std::vector<std::string> weaponsProficient;
		std::vector<std::string> armourProficient;
};