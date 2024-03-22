#pragma once
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>

//an abstract class that contains methods and attributes to display sprites to the user
class drawable {
	protected:
		std::vector<sf::Texture> textArray;//an array of texture:used for animation
		//path to find the textures, starts from cmd
		std::string imagePath;// mut be in form "Resources\\folder\\folder"
		void loadTextures();// load the textures from file.
	public:
		int currentText = 0;//the postion in the array
		sf::Vector2f localPosition;//actual position on the screen
		sf::Vector2f tile;//Which tile it is on
		sf::Sprite sprite;// the sprite object
		sf::Sprite draw();//draw the sprite
		void changeSpriteText(std::string textArgs = "next");//change the texture of the sprite
};
