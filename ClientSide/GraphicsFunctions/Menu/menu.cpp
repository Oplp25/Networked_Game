#include "menu.h"
#include<SFML\Graphics.hpp>

void runMenu(sf::RenderWindow& win) {
	sf::Event event;
	while (win.isOpen()) {
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				win.close();
			}
		}
		win.clear(sf::Color::Blue);
		win.display();
	}
}