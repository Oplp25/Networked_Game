#pragma once
#include<SFML/Graphics.hpp>
#include "../GraphicsFunctions/drawable/drawable.h"

class entity:public drawable {

	protected:
		void switchTextArray(char direction, char d2 = ' ', char d3 = ' ');//direction is the direction, or a if attacking. d2 is left or right when attacking, d3 is the direction you are attacking in(only for the player)
		std::vector<std::vector<sf::Texture>> listOfTexts = { {},{},{},{},{},{},{} };// up, down,right, still, rightAttack, upRightAttack,downRightAttack	
		float speed;

		bool checkEnd(char direction, int nums = 0);//Checks whether a character is going to move off the edge of the map. returns true if the move is OK
	public:
		char entityCurrentDirection = 's';
		bool damaged = false;
		int damageTick = 0;
		int hpMax;
		int hpCurrent;
		int attackTick = 0;
		int maxAttackTick = 3;
		bool attacking = false;
		std::string name;
		void changeSpriteText(std::string textArgs);
		void loadTextures();
		entity();
		void attack(entity &ent, int damage);
		void move(char direction, std::vector<std::vector<sf::Vector2f*>> collObjs);
		void damageSelf(int damage);
		void death();
		void spawn();


};