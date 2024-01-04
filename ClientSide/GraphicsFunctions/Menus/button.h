#pragma once
#include<SFML/Graphics.hpp>

//struct for menu buttons
struct button {
	button(void (*func)(sf::RenderWindow&), sf::RectangleShape RectangleP);//constructor for buttons that are rectangles
	button(void (*func)(sf::RenderWindow&), sf::Sprite spriteP);//overloaded constructor for buttons that use sprites
	button(sf::RectangleShape RectangleP);
	button();
	sf::RectangleShape Rectangle;
	sf::Sprite sprite;
	sf::FloatRect hitbox;//the hitbox of the button
	void(*fncPtr)(sf::RenderWindow&);//function pointer taht points to the function that will be run after the menu button is clicked
	char des = 'm';//the designation
};