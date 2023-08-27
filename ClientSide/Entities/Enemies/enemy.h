#pragma once
#include "../entity.h"
class enemy :public entity {
	private:
		float aggro = 0.4;//likelyhood of chasing player
		int sight;//How far they can see the player from
		int damage;
		bool isRanged;
		float cooldown;
		int reach;//Melee
		int patrolRange;
		std::string typeName;// type of enemy, e.g. archer, mage
		std::string raceName;//race of enemy e.g. Orc, Skeleton
	public:
	std::string name;//formed of race name+ type name e.g. Orc Archer
};