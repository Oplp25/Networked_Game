#pragma once
#include "../item.h"
#include "weaponTemplates.h"
class weapon : public item {
	public:
		int damage;
		float cooldown;
		int reach;
		int hands;
		weapon();
		weapon(std::string pname, int pcost, int pcharges, std::string pimagePath, int pdamage, float pcooldown, int preach, int phands);
		weapon(weaponTemplate stats);
		//texture functions
		void loadTextures();
		void changeSpriteText(std::string textArgs);
		void switchTextArray(char direction, char d2 = ' ', char d3 = ' ');
		std::vector<std::vector<sf::Texture>> listOfTexts = { {},{},{},{},{},{},{} };// up, down, right, still, rightAttack, upRightAttack, downRightAttack
		char itemCurrentDirection = 'm';
	private:
};