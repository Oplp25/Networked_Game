#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include<vector>
#include "../entity.h"
#include "Races/raceIncluder.h"
#include "Classes/classIncluder.h"
#include "inventory.h"
#include "abilityScoresEnum.h"
#include "../../Items/Weapons/weapon.h"

class character :public entity {
	private:

		int xp;
		int level;
		int manaMax;//For Magical abilities
		int manaCurrent;
		int staminaMax;//For Physical abilities
		int staminaCurrent;
		int hpMax;
		int hpCurrent;
		int hitDiceType;
		std::vector<int> abilityScores;// the ability scores can be accessed by abilityScores[abilityScoreEnum]
		//vector<spell> spellList;
		inventory charInventory;
		bool canCastSpells;
		std::vector<std::string> weaponsProficient;
		std::vector<std::string> armourProficient;
		std::vector<abilityScoresEnum> savesProficient;//must have an END at the end
		weapon heldWeapon;
		void levelUp();

		//need an object of every class, and a pointer to archetype. Always call the pointer to archetype when trying to access methods/attributes
		paladin paladinObj;

		archetype* classPtr;

		int profBonus;
		void(*primaryPointer)(character*);//need to use std::invoke to call these functions. E.G, std::invoke(myCharacter.primaryPointer,myCharacter)
		void(*secondaryPointer)(character*);//need to use std::invoke to call these functions E.G, std::invoke(myCharacter.secondaryPointer,myCharacter)
		void(*defensivePointer)(character*);//need to use std::invoke to call these functions E.G, std::invoke(myCharacter.defensivePointer,myCharacter)
		void(*specialPointer)(character*);//need to use std::invoke to call these functions E.G, std::invoke(myCharacter.specialPointer,myCharacter)
		void(*buffPointer)(character*);//need to use std::invoke to call these functions E.G, std::invoke(myCharacter.buffPointer,myCharacter)
		void(*ultPointer)(character*);//need to use std::invoke to call these functions E.G, std::invoke(myCharacter.ultPointer,myCharacter)

		std::vector<void(archetype::*)()> levelUpFuncs;//when accessing, have to do levelUpFunc[level-2]. need to use std::invoke to call these functions, E.G, std::invoke(myCharacter.levelUpFuncs[myCharacter.level-2],myCharacter.classPtr)

		void setScores(std::vector<abilityScoresEnum> abilityScoreUpgrades, int maxManaIncrease, int maxHealthIncrease, int maxStaminaIncrease, float speed);//sets the maxes for mana, stamina and hp, also increases the ability scores and sets speed based on the race
		int hpIncrease();//returns the increase in hp
		//resistances/weaknesses
		//need to add something for the passive(s)
	public:
		character(std::string thisRace,std::string thisClass, std::string name, char error);
		character();
		std::string characterName;
		std::string className;
		std::string characterRace;
		weapon currentWeapon;
		int armourClass;
		
		void usePrimary();
		void useSecondary();
		void useDefensive();
		void useSpecial();
		void useBuff();
		void useUlt();

		int makeSave(abilityScoresEnum ability, char hasAdvantage = 'n');//char hasAdvantage - 'n' = normal, 'a' = advantage and 'd' = disadvantage
		int makeCheck(abilityScoresEnum ability, char hasAdvantage = 'n');//char hasAdvantage - 'n' = normal, 'a' = advantage and 'd' = disadvantage

		void gainXP(int xpGained);

		void changeSpriteText(std::string textArgs);
};