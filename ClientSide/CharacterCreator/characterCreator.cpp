#include "CharacterCreator.h"
#include "../colourConsts.h"
#include<filesystem>
#include<iostream>
#include<map>
#include<chrono>

using namespace std;
const filesystem::path cwd = filesystem::current_path();

bool spriteComp::operator()(const sf::Sprite& a, const sf::Sprite& b)const {
	if (a.getGlobalBounds().top == b.getGlobalBounds().top) {
		return a.getGlobalBounds().left < b.getGlobalBounds().left;
	}
	return a.getGlobalBounds().top < b.getGlobalBounds().top;
}
character characterCreator(sf::RenderWindow& win)
{
	bool happy = false;
	character myChar;
	char errorCode = 'n';
	while (!happy) {
		string classChoiceString = classPicker(win);
		if(classChoiceString == "False"){
			errorCode = 'e';
			happy = true;
		}
		string raceChoiceString = racePicker(win);
		if (raceChoiceString == "False") {
			errorCode = 'e';
			happy = true;
		}
		myChar = character(raceChoiceString,classChoiceString,"name",errorCode);
		happy = true;
	}
	return myChar;
}

std::string classPicker(sf::RenderWindow& win)
{
	vector<sf::Texture> textureList = {};
	map < sf::Sprite, string, spriteComp> iconList = {};//a map of sprites to strings, with the strings being the name of the class represented by the sprite. spriteComp is a method that compares sprites by their y position, then their x position
	vector<sf::Sprite> spriteList;
	int width = win.getSize().x;
	int height = win.getSize().y;
	int iconD = width / 7;
	int x = (width - (4 * iconD)) / 2;
	int y = height / 5;
	int count = 0;
	sf::Sprite s;
	for (string i : classList) {//need to do textureList and iconList in seperate functions
		textureList.push_back(sf::Texture());
		s = sf::Sprite();
		if (!textureList.back().loadFromFile(cwd.string() + "/Resources/ClassIcons/" + i + ".jpeg")) {
			cout << "Error: Failed to load \"" + i + ".jpeg\" from file" << endl;
			sf::Texture t;
			t.create(120, 120);
			textureList.back() = t;
		}
		s.setScale(iconD / 120, iconD / 120);
		s.setPosition(x, y);
		spriteList.push_back(s);
		x += iconD / 2;
		x += iconD;
		count++;
		if (count == 3) {
			count = 0;
			x = (width - (4 * iconD)) / 2;
			y += iconD;

		}
	}
	for (int i = 0; i < classList.size(); i++) {
		spriteList[i].setTexture(textureList[i]);
		iconList.emplace(spriteList[i],classList[i]);
	}
	sf::RectangleShape backButton = sf::RectangleShape(sf::Vector2f(width/7,height/8));
	backButton.setFillColor(colours::pistachio);
	backButton.setPosition(sf::Vector2f(width/30,height/20));
	sf::Font comicsans;
	if (!comicsans.loadFromFile(cwd.string() + "\\Resources\\Fonts\\ComicSans.ttf")) {
		cout << "Error. Failed to load font Comic Sans" << endl;
	}
	sf::Text backText = sf::Text("Back",comicsans,60);
	backText.setStyle(sf::Text::Bold);
	backText.setFillColor(sf::Color(0,0,0));
	backText.setPosition(sf::Vector2f(width/30+(backButton.getGlobalBounds().width-backText.getGlobalBounds().width)/2, height / 20 + (backButton.getGlobalBounds().height - backText.getGlobalBounds().height) / 2.5));
	
	sf::Text titleText = sf::Text("Pick Your Class", comicsans, 100);
	titleText.setStyle(sf::Text::Bold);
	titleText.setFillColor(colours::auburn);
	titleText.setPosition(sf::Vector2f((width-titleText.getGlobalBounds().width)/2,height/20));
	win.clear(colours::cinereous);
	win.display();
	bool selected = false;
	sf::Event event;
	while (!selected) {
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				win.close();
				return "False";
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mouseLoc = sf::Mouse::getPosition();
				sf::Vector2f mouseLocF = sf::Vector2f(mouseLoc.x, mouseLoc.y);
				for (auto i : iconList) {
					if (i.first.getGlobalBounds().contains(mouseLocF)) {
						return i.second;
					}
				}
				if (backButton.getGlobalBounds().contains(mouseLocF)) {
					return "False";
				}
			}
			win.clear(colours::cinereous);
			for (auto i : iconList) {
				win.draw(i.first);
			}
			win.draw(backButton);
			win.draw(backText);
			win.draw(titleText);
			win.display();
		}
	}
	return string();
}

string racePicker(sf::RenderWindow& win)
{
	return std::string();
}

string nameChooser(sf::RenderWindow& win)
{
	return std::string();
}
