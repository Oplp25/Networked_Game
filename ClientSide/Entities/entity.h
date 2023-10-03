#pragma once
#include<SFML/Graphics.hpp>
#include "../GraphicsFunctions/drawable/drawable.h"

class entity:public drawable {

	protected:
		void switchTextArray(char direction);
		std::vector<std::vector<sf::Texture>> listOfTexts = { {},{},{},{},{},{},{} };// up, down,right, still, rightAttack, upRightAttack,downRightAttack
		char entityCurrentDirection = 's';
		float speed;

		bool checkEnd(char direction, int nums = 0);//Checks whether a character is going to move off the edge of the map. returns true if the move is OK
	public:
		std::string name;
		void changeSpriteText(std::string textArgs);
		void loadTextures();
		int hpCurrent;
		int hpMax;
		sf::Vector2f tile;//Which tile it is on
		entity();
		void move(char direction);
		void damage();
		void death();
		void spawn();


};