#pragma once
#include<string>

struct enemyTemplate{
public:
	float aggro = 0.4;//likelyhood of chasing player
	int sight;//How far they can see the player from
	int damage;
	bool isRanged;
	float cooldown;
	int reach;//Melee
	int patrolRange;
	float speed;
	int hpMax;
	std::string name;
	std::string imagePath;
	enemyTemplate() {
		damage = 0;
		cooldown = 0;
		reach = 0;
		name = "";
		imagePath = "";
		aggro = 0;
		sight = 0;
		isRanged = 0;
		patrolRange = 0;
		speed = 0;
		hpMax = 1;
	}
	enemyTemplate(int hpMaxP, float speedP,std::string nameP, float aggroP, int sightP, int damageP, bool isRangedP, float cooldownP, int reachP, int patrolRangeP,std::string imagePathP) {
		damage = damageP;
		cooldown = cooldownP;
		reach = reachP;
		name = nameP;
		imagePath = imagePathP;
		aggro = aggroP;
		sight = sightP;
		isRanged = isRangedP;
		patrolRange = patrolRangeP;
		speed = speedP;
		hpMax = hpMaxP;
	}

};

const enemyTemplate orcSwordsman = enemyTemplate(14,3,"Orc Swordsman",0.5,300,4,false,0.1,2,250,"Resources\\Sprite Assets\\Orc Swordsman");