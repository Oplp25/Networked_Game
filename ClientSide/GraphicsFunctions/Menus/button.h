#pragma once
#include<SFML/Graphics.hpp>

struct button {
	button(void (*func)(sf::RenderWindow&), sf::RectangleShape RectangleP);
	button(void (*func)(sf::RenderWindow&), sf::Sprite spriteP);
	button(sf::RectangleShape RectangleP);
	button();
	sf::RectangleShape Rectangle;
	sf::Sprite sprite;
	sf::FloatRect hitbox;
	void(*fncPtr)(sf::RenderWindow&);
	char des = 'm';
};