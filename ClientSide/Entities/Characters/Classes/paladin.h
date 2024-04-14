#pragma once
#include "archetype.h"
#include<iostream>

//the paladin class
class paladin :public archetype {
	public:
		//override makes the function polymorphised
		int getHitDiceType() override;
		std::string getClassName() override;
		bool getCanCastSpells() override;
		std::vector<abilityScoresEnum> getSavesProficient() override;
		std::vector<std::string> getArmourProficient() override;
		std::vector<std::string> getWeaponsProficient() override;
		void primary() override;
		void secondary() override;
		void defensive() override;
		inventory getStartingEquipment() override;
		bool canCastSpells = true;
		std::vector<abilityScoresEnum> savesProficient = { WIS,CON };
		std::string className = "paladin";
		int hitDiceType = 10;
		std::vector<std::string> weaponsProficient;
		std::vector<std::string> armourProficient;
		inventory startingEquipment = inventory({weapon(swordTemplate)});//starting equipment i sjust a sword
};