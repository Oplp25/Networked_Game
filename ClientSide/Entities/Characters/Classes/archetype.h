#pragma once
#include<vector>
#include<map>
#include<string>
#include<SFML/Graphics.hpp>

#include "../inventory.h"
#include "../Races/race.h"
#include "../abilityScoresEnum.h"


class archetype {//A parent class of all of the classes. so they are called archetypes. All characters will be instances of the child classes of the archetype Class
	protected:
		//character-specific attributes
		int xp;
		int level;
		int manaMax;//For Magical abilities
		int manaCurrent;
		int staminaMax;//For Physical abilities
		int staminaCurrent;
		int hpMax;
		int hpCurrent;
		int hitDiceType;
		int speed;
		std::vector<int> abilityScores;// the ability scores can be accessed by abilityScores[abilityScoreEnum]
		//vector<spell> spellList;
		inventory inventory;

		//class-specific attributes
		bool canCastSpells;
		std::vector<std::string> weaponsProficient;
		std::vector<std::string> armourProficient;
		std::vector<abilityScoresEnum> savesProficient;//must have an END at the end


		void levelUp();

		int profBonus;
		void(*primaryPointer)(archetype*);
		void(*secondaryPointer)(archetype*);
		void(*defensivePointer)(archetype*);
		void(*specialPointer)(archetype*);
		void(*buffPointer)(archetype*);
		void(*ultPointer)(archetype*);

		void level2();
		void level3();
		void level4();
		void level5();
		void level6();
		void level7();
		void level8();
		void level9();
		void level10();
		void level11();
		void level12();
		void level13();
		void level14();
		void level15();
		void level16();
		void level17();
		void level18();
		void level19();
		void level20();
		
		std::vector<void(archetype::*)()> levelUpFuncs = {&level2,&level3,&level4,&level5,&level6,&level7,&level8,&level9,&level10,&level11,&level13,&level14,&level15,&level16,&level17,&level18,&level19,&level20 };//when accessing, have to do levelUpFunc[level-2]
		
		void setScores();//sets the maxes for mana, stamina and hp, also increases the ability scores and sets speed based on the race
		int hpIncrease();//returns the increase in hp
		//resistances/weaknesses
		//need to add something for the passive(s) - perhaps in the child classes
	public:

		archetype(race thisRace, std::string name);

		std::string characterName;
		std::string className;
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
		
		void gainXP(int xpGained);
};