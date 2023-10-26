#include "gameOutcomes.h"
#include "Colours/colourConsts.h"
#include<filesystem>
#include<iostream>

using namespace std;
const filesystem::path cwd = filesystem::current_path();

void spWin(sf::RenderWindow& win) {
	sf::Texture wonText;
	if (!wonText.loadFromFile(cwd.string()+"\\Resources\\outcomeScreens\\spWin.png")) {
		cout << "Error. spWin.png not loaded" << endl;
	}
	sf::Sprite wonSprite;
	wonSprite.setTexture(wonText);
	wonSprite.setOrigin(sf::Vector2f(wonSprite.getLocalBounds().width / 2, wonSprite.getLocalBounds().height / 2));
	wonSprite.setPosition(sf::Vector2f(win.getSize().x / 2, win.getSize().y / 2));
	sf::Event event;
	while (true){
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				return void();
			}
		}
		win.clear(colours::cinereous);
		win.draw(wonSprite);
		win.display();
	}
}

void spLoss(sf::RenderWindow& win){
	sf::Texture lossText;
	if (!lossText.loadFromFile(cwd.string() + "\\Resources\\outcomeScreens\\spLoss.png")) {
		cout << "Error. spWin.png not loaded" << endl;
	}
	sf::Sprite lossSprite;
	lossSprite.setTexture(lossText);
	lossSprite.setOrigin(sf::Vector2f(lossSprite.getLocalBounds().width / 2, lossSprite.getLocalBounds().height / 2));
	lossSprite.setPosition(sf::Vector2f(win.getSize().x / 2, win.getSize().y / 2));
	sf::Event event;
	while (true) {
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				return void();
			}
		}
		win.clear(colours::cinereous);
		win.draw(lossSprite);
		win.display();
	}
}