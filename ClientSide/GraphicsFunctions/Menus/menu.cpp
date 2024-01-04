#include "menu.h"
#include<SFML\Graphics.hpp>
#include<iostream>
#include<vector>
#include<future>
#include<filesystem>

#include "../Colours/colourConsts.h"
#include "arenaFighterTeamsMenu.h"
#include "arenaFighterMenu.h"
#include "../../ArenaFighter/arenaFighterMain.h"
#include "button.h"
#include "../../ConnectionFunctions/serverConnection.h"
using namespace std;
using namespace colours;

const filesystem::path cwd = filesystem::current_path();

void runMenu(sf::RenderWindow& win, bool online) {
	int width = win.getSize().x;
	int height = win.getSize().y;
	sf::Font comicsans;
	if (!comicsans.loadFromFile(cwd.string() + "\\Resources\\Fonts\\ComicSans.ttf")) {
		cout << "Error. Failed to load font Comic Sans" << endl;
	}

	sf::RectangleShape networkStatusShape;
	button networkStatusButton;
	sf::Text networkStatusText;
	if (online) {
		
	}
	else {
		networkStatusShape = sf::RectangleShape(sf::Vector2f(width/6,height/12));
		networkStatusShape.setPosition(sf::Vector2f(width/20,height/20));
		networkStatusShape.setFillColor(cinereous);

		networkStatusButton = button(networkStatusShape);
		networkStatusButton.des = 's';

		networkStatusText.setString("Reconnect");
		networkStatusText.setCharacterSize(60);
		networkStatusText.setFillColor(sf::Color(0, 0, 0));
		networkStatusText.setStyle(sf::Text::Bold);
		networkStatusText.setFont(comicsans);
		networkStatusText.setPosition(sf::Vector2f(networkStatusShape.getPosition().x + (networkStatusShape.getLocalBounds().width - networkStatusText.getLocalBounds().width) / 2, networkStatusShape.getPosition().y+width/190));
	}
	//RectShapes
	sf::RectangleShape dungeonButtonShape(sf::Vector2f(width/2,height/9));
	dungeonButtonShape.setPosition(sf::Vector2f(width/4, 7 * height/9));
	dungeonButtonShape.setFillColor(cinereous);
	sf::RectangleShape arenaButtonShape(sf::Vector2f(width / 2,  height / 9));
	arenaButtonShape.setPosition(sf::Vector2f(width / 4, 5 * height / 9));
	arenaButtonShape.setFillColor(cinereous);

	vector<sf::RectangleShape> rectShapeList = { arenaButtonShape, dungeonButtonShape, networkStatusShape };

	//Sprites
	vector<sf::Sprite> spriteList;

	//buttons
	button arenaButton = button(&runArenaFighterMenu, arenaButtonShape);
	button dungeonButton = button(&runArenaFighterTeamsMenu, dungeonButtonShape);

	vector<button> buttonList = {arenaButton,dungeonButton,networkStatusButton};

	//text
	sf::Text arenaText;
	arenaText.setString("Arena Fighter Solos");
	arenaText.setCharacterSize(90);
	arenaText.setFillColor(sf::Color(0, 0, 0));
	arenaText.setStyle(sf::Text::Bold);
	arenaText.setFont(comicsans);
	arenaText.setPosition(sf::Vector2f(arenaButtonShape.getPosition().x+(arenaButtonShape.getLocalBounds().width - arenaText.getLocalBounds().width)/2, arenaButtonShape.getPosition().y));

	sf::Text dungeonText;
	dungeonText.setString("Arena Fighter Teams");
	dungeonText.setCharacterSize(90);
	dungeonText.setFillColor(sf::Color(0, 0, 0));
	dungeonText.setStyle(sf::Text::Bold);
	dungeonText.setFont(comicsans);
	dungeonText.setPosition(sf::Vector2f(dungeonButtonShape.getPosition().x + (dungeonButtonShape.getLocalBounds().width - dungeonText.getLocalBounds().width) / 2, dungeonButtonShape.getPosition().y));

	vector<sf::Text> textList = { arenaText, dungeonText, networkStatusText };

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
						if (i.des == 'm'){//if the button opens up a menu
							i.fncPtr(win);
						}
						else if (i.des == 's') {
							online = connectToServer(win);
						}
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

		for (sf::Text i : textList) {
			win.draw(i);
		}
		win.display();
	}
}