#include "menu.h"
#include<SFML\Graphics.hpp>
#include<iostream>
#include<vector>

#include "../Colours/colourConsts.h"
#include "dungeonCrawlerMenu.h"
#include "arenaFighterMenu.h"

using namespace std;
using namespace colours;

struct button {
	button(char sType, void (*func)(sf::RenderWindow&), sf::RectangleShape RectangleP = sf::RectangleShape(), sf::Sprite spriteP = sf::Sprite()) {
		if (sType == 115) {// s
			sprite = spriteP;
			hitbox = sprite.getGlobalBounds();
		}
		else if (sType == 114) {// r
			Rectangle = RectangleP;
			hitbox = Rectangle.getGlobalBounds();
		}
		else {
			cout << "Error, wrong symbol entered in struct button" << endl;
		}
		fncPtr = func;
	}
	sf::RectangleShape Rectangle;
	sf::Sprite sprite;
	sf::FloatRect hitbox;
	void(*fncPtr)(sf::RenderWindow&);
};

void runMenu(sf::RenderWindow& win) {
	int width = win.getSize().x;
	int height = win.getSize().y;


	sf::RectangleShape dungeonButtonShape(sf::Vector2f(width/2,height/9));
	dungeonButtonShape.setPosition(sf::Vector2f(width/4, 7 * height/9));
	dungeonButtonShape.setFillColor(cinereous);
	sf::RectangleShape arenaButtonShape(sf::Vector2f(width / 2,  height / 9));
	arenaButtonShape.setPosition(sf::Vector2f(width / 4, 5 * height / 9));
	arenaButtonShape.setFillColor(cinereous);

	vector<sf::RectangleShape> rectShapeList = { arenaButtonShape, dungeonButtonShape };

	vector<sf::Sprite> spriteList;
	button arenaButton = button('r', &runArenaFighterMenu, arenaButtonShape);
	button dungeonButton = button('r', & runDungeonCrawlerMenu, dungeonButtonShape);

	vector<button> buttonList = {arenaButton,dungeonButton};
	sf::Event event;
	while (win.isOpen()) {
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				win.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mouseLoc = sf::Mouse::getPosition();
				sf::Vector2f mouseLocF = sf::Vector2f(mouseLoc.x, mouseLoc.y);
				for (button i : buttonList) {
					if (i.hitbox.contains(mouseLocF)) {
						i.fncPtr(win);
					}
				}
			}
		}
		win.clear(pistachio);
		for (sf::RectangleShape i: rectShapeList) {
			win.draw(i);
		}
#
		for (sf::Sprite i : spriteList) {
			win.draw(i);
		}
		win.display();
	}
}