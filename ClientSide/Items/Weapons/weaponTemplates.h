#pragma once
#include<string>
#include "../itemTemplates.h"

//template for weapons
struct weaponTemplate :itemTemplate {
	int damage;
	float cooldown;
	int reach;
	int hands;
	weaponTemplate() {
		damage = 0;
		cooldown = 0;
		reach = 0;
		hands = 0;
	}
	weaponTemplate(std::string pname, int pcost, int pcharges, std::string pimagePath,int pdamage, float pcooldown, int preach, int phands) {
		damage = pdamage;
		cooldown = pcooldown;
		reach = preach;
		hands = phands;
		//itemTemplate constructor
		construct(pname, pcost, pcharges, true, pimagePath);
	}

};
const weaponTemplate swordTemplate = weaponTemplate("Sword", 5, 30, "Resources\\Sprite Assets\\Weapons\\sword", 5, 0.3, 75, 1);
//const weaponTemplate shortswordTemplate = weaponTemplate("Broken Stick", 5, 120, "", 10, 0.01, 20, 1);//Freddie Designed, Broken weapon
//const weaponTemplate warhammerTemplate = weaponTemplate("Warhammer", 7, 100, "", 10, 1, 75, 1);