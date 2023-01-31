#include "menu.h"
#include<SFML\Graphics.hpp>
#include "../Colours/colourConsts.h"
#include<vector>

using namespace std;
using namespace colours;
void runMenu(sf::RenderWindow& win) {
	int width = win.getSize().x;
	int height = win.getSize().y;
	sf::RectangleShape dungeonButton(sf::Vector2f(width/2,height/9));
	dungeonButton.setPosition(sf::Vector2f(width/4, 7 * height/9));
	dungeonButton.setFillColor(cinereous);
	sf::RectangleShape arenaButton(sf::Vector2f(width / 2,  height / 9));
	arenaButton.setPosition(sf::Vector2f(width / 4, 5 * height / 9));
	arenaButton.setFillColor(cinereous);
	vector<sf::RectangleShape> buttonList = {arenaButton,dungeonButton};
	sf::Event event;
	while (win.isOpen()) {
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				win.close();
			}
		}
		win.clear(pistachio);
		for (sf::RectangleShape i : buttonList) {
			win.draw(i);
		}
		win.display();
	}
}