#include<SFML/Graphics.hpp>
#include<filesystem>
#include<iostream>
#include<chrono>
using namespace std;

const filesystem::path cwd = filesystem::current_path();

void displayText(sf::RenderWindow& win, sf::Text txt, sf::Color backgroundColour);
void runIntro(sf::RenderWindow& win) {

	sf::Color backgroundColour(71, 168, 189);
	sf::Font comicsans;
	if (!comicsans.loadFromFile(cwd.string()+"\\Resources\\Fonts\\ComicSans.ttf")) {
		cout << "Error. Failed to load font Comic Sans" << endl;
	}
	sf::Text presentsText;
	presentsText.setString("Jakob Wood Presents");
	presentsText.setCharacterSize(100);
	presentsText.setFillColor(sf::Color(0,0,0,0));
	presentsText.setStyle(sf::Text::Bold);
	presentsText.setFont(comicsans);
	presentsText.setPosition(sf::Vector2f((win.getSize().x - presentsText.getLocalBounds().width) / 2, ((win.getSize().y - presentsText.getLocalBounds().height) / 2 - (win.getSize().y / 6))));
	
	displayText(win, presentsText, backgroundColour);
}

void displayText(sf::RenderWindow& win, sf::Text txt, sf::Color backgroundColour) {

	for (int i = 0; i < 256; i += 2){
		win.clear(backgroundColour);
		txt.setFillColor(sf::Color(0,0,0,i));
		win.draw(txt);
		win.display();
		this_thread::sleep_for(0.01s);
	}
	for (int i = 256; i > 0; i -= 2) {
		win.clear(backgroundColour);
		txt.setFillColor(sf::Color(0, 0, 0, i));
		win.draw(txt);
		win.display();
		this_thread::sleep_for(0.01s);
	}
}