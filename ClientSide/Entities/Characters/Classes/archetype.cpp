#include "archetype.h"
#include<iostream>

int archetype::getHitDiceType()
{
	return hitDiceType;
}

std::string archetype::getClassName()
{
	return className;
}

bool archetype::getCanCastSpells()
{
	return canCastSpells;
}

inventory archetype::getStartingEquipment()
{
	return startingEquipment;
}

std::vector<abilityScoresEnum> archetype::getSavesProficient()
{
	return savesProficient;
}

std::vector<std::string> archetype::getArmourProficient()
{
	return armourProficient;
}

std::vector<std::string> archetype::getWeaponsProficient()
{
	return weaponsProficient;
}

void archetype::primary() {
	std::cout << "primary" << std::endl;
}
void archetype::secondary() {
	std::cout << "secondary" << std::endl;
}
void archetype::defensive() {
	std::cout << "defensive" << std::endl;
}
void archetype::special() {
	std::cout << "special" << std::endl;
}
void archetype::buff() {
	std::cout << "buff" << std::endl;
}
void archetype::ult() {
	std::cout << "ult" << std::endl;
}
void archetype::level2()
{
}

void archetype::level3()
{
}


void archetype::level4()
{
}

void archetype::level5()
{
}

void archetype::level6()
{
}

void archetype::level7()
{
}

void archetype::level8()
{
}

void archetype::level9()
{
}

void archetype::level10()
{
}

void archetype::level11()
{
}

void archetype::level12()
{
}

void archetype::level13()
{
}

void archetype::level14()
{
}

void archetype::level15()
{
}

void archetype::level16()
{
}

void archetype::level17()
{
}

void archetype::level18()
{
}

void archetype::level19()
{
}

void archetype::level20()
{
}
