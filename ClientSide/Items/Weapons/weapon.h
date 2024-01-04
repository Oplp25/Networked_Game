#pragma once
#include "../item.h"
#include "weaponTemplates.h"
class weapon : public item {
	public:
		int damage;
		float cooldown;
		int reach;
		int hands;
		weapon();//empty constructor
		weapon(std::string pname, int pcost, int pcharges, std::string pimagePath, int pdamage, float pcooldown, int preach, int phands);//variable constructor
		weapon(weaponTemplate stats);//template constructor
		//texture functions
		void loadTextures();//load textures from file
		void changeSpriteText(std::string textArgs);//change the texture of the sprite
		void switchTextArray(char direction, char d2 = ' ', char d3 = ' ');//change which texture array is textArray
		std::vector<std::vector<sf::Texture>> listOfTexts = { {},{},{},{},{},{},{} };// up, down, right, still, rightAttack, upRightAttack, downRightAttack
		char itemCurrentDirection = 'm';
	private:
};