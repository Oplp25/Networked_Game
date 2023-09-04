#pragma once
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>


class drawable {
	protected:
		std::vector<sf::Texture> textArray;
		int currentText = 0;
		std::string imagePath;// mut be in form "Resources\\folder\\folder"
		void loadTextures();
	public:
		sf::Vector2f localPosition;//actual position on the screen
		sf::Sprite sprite;
		sf::Sprite draw();
		void changeSpriteText(std::string textArgs = "next");
};
