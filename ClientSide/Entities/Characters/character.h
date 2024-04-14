#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include<vector>
#include<memory>
#include "../entity.h"
#include "../Enemies/enemy.h"
#include "Races/raceIncluder.h"
#include "Classes/classIncluder.h"
#include "inventory.h"
#include "abilityScoresEnum.h"
#include "../../Items/Weapons/weapon.h"

class character :public entity {//inherits from entity
	private:

		int xp;//your xp
		int level;//your level
		int manaMax;//For Magical abilities
		int manaCurrent;
		int staminaMax;//For Physical abilities
		int staminaCurrent;
		int hitDiceType;//the hit dice
		std::vector<int> abilityScores;// the ability scores can be accessed by abilityScores[abilityScoreEnum]
		//vector<spell> spellList;
		inventory charInventory;//what equipment you have
		bool canCastSpells;
		std::vector<std::string> weaponsProficient;//what weapons you can use
		std::vector<std::string> armourProficient;//what armour you can use
		std::vector<abilityScoresEnum> savesProficient;//must have an END at the end
		void levelUp();//function that is called when you level up

		//need an object of every class, and a pointer to archetype. Always call the pointer to archetype when trying to access methods/attributes
		paladin paladinObj;

		archetype* classPtr;

		int profBonus;


		std::vector<void(archetype::*)()> levelUpFuncs;//when accessing, have to do levelUpFunc[level-2]. need to use std::invoke to call these functions, E.G, std::invoke(myCharacter.levelUpFuncs[myCharacter.level-2],myCharacter.classPtr)

		void setScores(std::vector<abilityScoresEnum> abilityScoreUpgrades, int maxManaIncrease, int maxHealthIncrease, int maxStaminaIncrease, float speed);//sets the maxes for mana, stamina and hp, also increases the ability scores and sets speed based on the race
		int hpIncrease();//returns the increase in hp
		//resistances/weaknesses
		//need to add something for the passive(s)
	public:
		character(std::string thisRace,std::string thisClass, std::string name, char error);//constructor
		character();//empty constructor, for arrays and blanks
		std::string characterName;//Your character's name
		std::string className;//Their class
		std::string characterRace;//their race
		weapon currentWeapon;//The weapon they have equipped
		int armourClass;//the armour strength
		
		//ability methods
		void usePrimary(std::vector<enemy>& enemyArray);
		void useSecondary();
		void useDefensive();

		//methods to attack
		void attack(entity& ent, int damage);
		void attack();

		//method to get various values from the archetype pointer
		void classSetUp();

		//methods to make saves or checks
		int makeSave(abilityScoresEnum ability, char hasAdvantage = 'n');//char hasAdvantage - 'n' = normal, 'a' = advantage and 'd' = disadvantage
		int makeCheck(abilityScoresEnum ability, char hasAdvantage = 'n');//char hasAdvantage - 'n' = normal, 'a' = advantage and 'd' = disadvantage

		//method to gain xp
		void gainXP(int xpGained);

		//method to change current texture
		void changeSpriteText(std::string textArgs);

		//method to draw it
		sf::Sprite draw();
};