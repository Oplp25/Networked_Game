#pragma once
#include<vector>
#include<string>

#include "../inventory.h"
#include "../Races/raceIncluder.h"
#include "../abilityScoresEnum.h"

class archetype {//A parent class of all of the classes. so they are called archetypes.
	public:
		std::vector<std::string> weaponsProficient;
		std::vector<std::string> armourProficient;
		std::vector<abilityScoresEnum> savesProficient;//must have an END at the end

		virtual void level2();
		virtual void level3();
		virtual void level4();
		virtual void level5();
		virtual void level6();
		virtual void level7();
		virtual void level8();
		virtual void level9();
		virtual void level10();
		virtual void level11();
		virtual void level12();
		virtual void level13();
		virtual void level14();
		virtual void level15();
		virtual void level16();
		virtual void level17();
		virtual void level18();
		virtual void level19();
		virtual void level20();

		std::vector<void(archetype::*)()> classLevelUpFuncs = { &archetype::level2,&archetype::level3,&archetype::level4,&archetype::level5,&archetype::level6,&archetype::level7,&archetype::level8,&archetype::level9,&archetype::level10,&archetype::level11,&archetype::level13,&archetype::level14,&archetype::level15,&archetype::level16,&archetype::level17,&archetype::level18,&archetype::level19,&archetype::level20 };
		//resistances/weaknesses
		//need to add something for the passive(s) - perhaps in the child classes
};