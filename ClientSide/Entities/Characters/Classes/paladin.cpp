#include "paladin.h"

int paladin::getHitDiceType()
{
	return hitDiceType;
}

std::string paladin::getClassName()
{
	return className;
}

bool paladin::getCanCastSpells()
{
	return canCastSpells;
}

std::vector<abilityScoresEnum> paladin::getSavesProficient()
{
	return savesProficient;
}

std::vector<std::string> paladin::getArmourProficient()
{
	return armourProficient;
}

std::vector<std::string> paladin::getWeaponsProficient()
{
	return weaponsProficient;
}

inventory paladin::getStartingEquipment()
{
	return startingEquipment;
}
void paladin::primary() {
	std::cout << "primary paladin" << std::endl;
}
void paladin::secondary() {
	std::cout << "secondary" << std::endl;
}
void paladin::defensive() {
	std::cout << "defensive" << std::endl;
}