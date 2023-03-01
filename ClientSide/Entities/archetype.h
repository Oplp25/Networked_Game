#pragma once
#include<vector>
#include<map>
#include<string>
#include<SFML/Graphics.hpp>

#include "../inventory.h"
#include "../Races/race.h"
#include "../abilityScoresEnum.h"

class Archetype {//A parent class of all of the classes. so they are called Archetypes. All characters will be instances of the child classes of the Archetype Class
	private:
		bool canCastSpells;
		std::vector<std::string> weaponsProficient;
		std::vector<std::string> armourProficient;
		std::vector<std::string> savesProficient;
		int manaMax;
		int manaCurrent;
		inventory inventory;

		int STR;
		int DEX;
		int CON;
		int INT;
		int WIS;
		int CHA;

		std::vector<int> abilityScores;

		int profBonus;
		void(*primaryPointer);
		void(*secondaryPointer);
		void(*defensivePointer);
		void(*specialPointer);
		void(*buffPointer);
		void(*ultPointer);

		//need to add something for the passive(s) - perhaps in the child classes
	public:
		std::string nameOfClass;
		race characterRace;
		int armourClass;

		void usePrimary();
		void useSecondary();
		void useDefensive();
		void useSpecial();
		void useBuff();
		void useUlt();

		int makeSave(abilityScoresEnum ability, char hasAdvantage = 'n');//char hasAdvantage - 'n' = normal, 'a' = advantage and 'd' = disadvantage
		int makeCheck(abilityScoresEnum ability, char hasAdvantage = 'n');//char hasAdvantage - 'n' = normal, 'a' = advantage and 'd' = disadvantage
};