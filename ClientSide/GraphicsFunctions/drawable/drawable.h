#pragma once
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>


class drawable {
	private:
		std::vector<sf::Texture> textArray;
		int currentText;
		sf::Sprite sprite;
		std::string imagePath;// mut be in form "folder\\folder\\folder"
		std::vector<sf::Texture> loadTextures();
	public:
		sf::Sprite draw();
		void changeSpriteText(std::string textArgs = "next");
};
