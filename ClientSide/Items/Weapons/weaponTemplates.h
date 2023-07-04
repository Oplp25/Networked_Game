#pragma once
#include<string>
#include "../itemTemplates.h"

struct weaponTemplate :itemTemplate {
	int damage;
	float cooldown;
	int reach;
	weaponTemplate() {
		damage = 0;
		cooldown = 0;
		reach = 0;
	}
	weaponTemplate(std::string pname, int pcost, int pcharges, std::string pimagePath,int pdamage, float pcooldown, int preach) {
		damage = pdamage;
		cooldown = pcooldown;
		reach = preach;
		construct(pname, pcost, pcharges, true, pimagePath);
	}

};

const weaponTemplate swordTemplate = weaponTemplate("Sword", 5, 30, "", 5, 1, 2);
const weaponTemplate shortswordTemplate = weaponTemplate("Broken Stick", 5, 120, "", 10, 0.01, 20);//Freddie Designed, Broken weapon