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

weapon paladin::getStartingWeapon() {
	return startingWeapon;
}
