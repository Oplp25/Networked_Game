#pragma once
#include<SFML/Graphics.hpp>
#include "../GraphicsFunctions/drawable/drawable.h"

class entity:public drawable {

	protected:
		sf::Vector2f actualPos;//actual position on the map
		void switchTextArray(char direction);
		std::vector<std::vector<sf::Texture>> listOfTexts = { {},{},{},{},{} };// up, down, left, right, misc
	public:
		void changeSpriteText(std::string textArgs);
		void loadTextures();
		int hpCurrent;
		int hpMax;
		sf::Vector2f tilePos;//Position on the tile that it it on
		sf::Vector2f tile;//Position of the tile that it is on
		entity();
		void move();
		void damage();
		void death();
		void spawn();
		void meleeAttack();


};