#pragma once
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>


class drawable {
	protected:
		std::vector<sf::Texture> textArray;
		int currentText;
		sf::Sprite sprite;
		std::string imagePath;// mut be in form "folder\\folder\\folder"
		void loadTextures();
	public:
		sf::Sprite draw();
		void changeSpriteText(std::string textArgs = "next");
};
