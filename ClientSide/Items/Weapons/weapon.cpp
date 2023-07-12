#include "weapon.h"

using namespace std;

weapon::weapon(){
	name = "Blank";
	cost = 0;
	charges = 1;
	consumable = true;
	imagePath = "";
	damage = 0;
	cooldown = 0;
	reach = 0;
	hands = 0;
}

weapon::weapon(std::string pname, int pcost, int pcharges, std::string pimagePath, int pdamage, float pcooldown, int preach, int phands){
	name = pname;
	cost = pcost;
	charges = pcharges;
	consumable = true;
	imagePath = pimagePath;
	damage = pdamage;
	cooldown = pcooldown;
	reach = preach;
	hands = phands;

}
weapon::weapon(weaponTemplate stats){
	name = stats.name;
	cost = stats.cost;
	charges = stats.charges;
	consumable = true;
	imagePath = stats.imagePath;
	damage = stats.damage;
	cooldown = stats.cooldown;
	reach = stats.reach;
	hands = stats.hands;
}