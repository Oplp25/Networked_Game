#include "CharacterCreator.h"
#include "../GraphicsFunctions/Colours/colourConsts.h"
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
		//string classChoiceString = "paladin";
		string classChoiceString = classPicker(win);
		if(classChoiceString == "False"){
			errorCode = 'e';
			break;
		}
		//string raceChoiceString = "dwarf";
		string raceChoiceString = racePicker(win, classChoiceString);
		if (raceChoiceString == "Unhappy") {

			continue;
		}
		string name;
		//name = "Jeff";
		name =  nameChooser(win);
		happy = happyChooser(win,name,classChoiceString,raceChoiceString);
		if (happy) {
			myChar = character(raceChoiceString,classChoiceString,name,errorCode);
		}
	}
	myChar.classSetUp();
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

	sf::RectangleShape exitButton = sf::RectangleShape(sf::Vector2f(width / 16, height / 16));
	exitButton.setPosition(sf::Vector2f(7 * width / 8, 14 * height / 16));
	exitButton.setFillColor(colours::pacificBlue);

	sf::RectangleShape selectionHighlight = sf::RectangleShape(sf::Vector2f(spriteList[0].getGlobalBounds().width + 40, spriteList[0].getGlobalBounds().height + 40));
	selectionHighlight.setFillColor(colours::pacificBlue);

	win.clear(colours::cinereous);
	win.display();
	string currentSelection;
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
				for (auto i : iconList) {//iterating over the map
					if (i.first.getGlobalBounds().contains(mouseLocF)) {//if the user clicked on this icon
						currentSelection = i.second;//class name - string
						selectionHighlight.setPosition(i.first.getPosition().x - 20, i.first.getPosition().y - 20);//place the outline on that icon
					}
				}
				if (backButton.getGlobalBounds().contains(mouseLocF)) {
					return "False";
				}
				if (exitButton.getGlobalBounds().contains(mouseLocF)) {
					return currentSelection;
				}
			}
			win.clear(colours::cinereous);
			if (currentSelection != "") {
				win.draw(selectionHighlight);
			}
			for (auto i : iconList) {
				win.draw(i.first);
			}
			win.draw(exitButton);
			win.draw(backButton);
			win.draw(backText);
			win.draw(titleText);
			win.display();
		}
	}
	return string();
}

string racePicker(sf::RenderWindow& win, string classStr)
{
	filesystem::path charPath = cwd.string() + "/Resources/RaceIcons/"+classStr+"/";
	int width = win.getSize().x;
	int height = win.getSize().y;

	vector<sf::Text> textList;
	sf::Texture currentImgText;
	sf::Sprite currentImgSprite;
	currentImgSprite.setPosition(sf::Vector2f(5*width/8,height/4));

	sf::Font comicsans;
	if (!comicsans.loadFromFile(cwd.string() + "\\Resources\\Fonts\\ComicSans.ttf")) {
		cout << "Error. Failed to load font Comic Sans" << endl;
	}
	int x = width/8;
	int y = height/8;
	string k;
	for (string i : raceList) {
		k = i;
			for (int j = 0; j < k.length(); j++) {
				if (j == 0) {
					k[0] -= 32;
				}
				else if (k[j-1]==' ') {
					k[j] -= 32;
				}
		}
		textList.push_back(sf::Text(k,comicsans));
		textList[textList.size()-1].setPosition(x, y);
		y += (3 * height / 4) / 9;
	}
	string currentSelection = "dwarf";
	if (!currentImgText.loadFromFile(charPath.string() + currentSelection + ".png")) {
		cout << "Error. Could not load file " + currentSelection + ".png" << endl;
		currentImgText.loadFromFile(charPath.parent_path().parent_path().string() + "/characterUnavailable.png");
	}
	currentImgSprite.setTexture(currentImgText);
	currentImgSprite.setScale(10,10);
	sf::RectangleShape selectionHighlight = sf::RectangleShape(sf::Vector2f(width/8,height/16));
	selectionHighlight.setPosition(sf::Vector2f(textList[2].getPosition().x - width / 32, textList[2].getPosition().y - height / 64));
	selectionHighlight.setFillColor(colours::pacificBlue);

	sf::RectangleShape exitButton = sf::RectangleShape(sf::Vector2f(width / 8, height / 16));
	exitButton.setPosition(sf::Vector2f(6*width/8,14*height/16));
	exitButton.setFillColor(colours::pacificBlue);
	bool chose = false;
	sf::Event event;
	while (!chose) {
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				win.close();
				return "False";
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mouseLoc = sf::Mouse::getPosition(win);
				sf::Vector2f mouseLocF = sf::Vector2f(mouseLoc.x, mouseLoc.y);
				for (int i = 0; i < 9; i++) {//iterate over the array containing the sprites
					if (textList[i].getGlobalBounds().contains(mouseLocF)) {//if the user clicked this sprite
						currentSelection = raceList[i];//class name
						if (!currentImgText.loadFromFile(charPath.string() + currentSelection + ".png")) {//load image file from storage
							cout << "Error. Could not load file " + currentSelection + ".png" << endl;//error message
							if (!currentImgText.loadFromFile(cwd.string() + "/Resources/RaceIcons/characterUnavailable.png")) {//load the placeholder sprite
								cout << "Error.Could not load file characterUnavailable.png" << endl;//error message
							}
						}
						currentImgSprite.setTexture(currentImgText);//set texture of figure on left of the screen
						selectionHighlight.setPosition(sf::Vector2f(textList[i].getPosition().x-width/32, textList[i].getPosition().y-height/64));//highlight name on screen
					}
				}
				if (exitButton.getGlobalBounds().contains(mouseLocF)) {
					return currentSelection;
				}
			}
		}
		win.clear(colours::cinereous);
		win.draw(selectionHighlight);
		for (sf::Text i : textList) {
			win.draw(i);
		}
		win.draw(currentImgSprite);
		win.draw(exitButton);
		win.display();
	}
	return std::string();
}

string nameChooser(sf::RenderWindow& win)
{
	int width = win.getSize().x;
	int height = win.getSize().y;

	sf::Font comicsans;
	if (!comicsans.loadFromFile(cwd.string() + "\\Resources\\Fonts\\ComicSans.ttf")) {
		cout << "Error. Failed to load font Comic Sans" << endl;
	}

	sf::RectangleShape textInpRect = sf::RectangleShape(sf::Vector2f(width/2,height/16));
	textInpRect.setPosition(sf::Vector2f(width/4,15*height/32));
	textInpRect.setFillColor(colours::auburn);

	sf::Text helpText = sf::Text("Please enter your character's name:", comicsans,50);
	helpText.setPosition(sf::Vector2f(width / 4 +(width/2 - helpText.getGlobalBounds().width)/2,14*height/32 - helpText.getGlobalBounds().height));

	sf::RectangleShape exitButton = sf::RectangleShape(sf::Vector2f(width / 8, height / 16));
	exitButton.setPosition(sf::Vector2f(6.5 * width / 8, 14 * height / 16));
	exitButton.setFillColor(colours::pacificBlue);

	sf::Text exitText = sf::Text("Continue",comicsans,30);
	exitText.setPosition(sf::Vector2f((6.5 * width / 8)+(( width / 8)-exitText.getGlobalBounds().width)/2, (14* height / 16) + ((height / 16)-exitText.getGlobalBounds().height) / 2));

	string name;
	sf::Text nameText = sf::Text("",comicsans,30);
	nameText.setPosition(sf::Vector2f(width/4+ (width / 2 - nameText.getGlobalBounds().width) / 2,15*height/32+(height/16-nameText.getGlobalBounds().height)/2));
	bool chose = false;
	sf::Event event;
	while (!chose) {
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				win.close();
				return "False";
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mouseLoc = sf::Mouse::getPosition();
				sf::Vector2f mouseLocF = sf::Vector2f(mouseLoc.x, mouseLoc.y);
				if (exitButton.getGlobalBounds().contains(mouseLocF)) {
					return name;
				}
			}
			if (event.type == sf::Event::TextEntered) {//If text is entered
				if (static_cast<char>(event.text.unicode) == 8) {//if the character was a backspace
					if (name.size() > 0) {
						name.pop_back();//delete the last letter
					}
				}
				else {
					name += static_cast<char>(event.text.unicode);//add the character the user typed to the name
				}
				nameText.setString(name);//Update the onscreen name
				//adjust position and size of name so that it stays in the text box
				nameText.setPosition(sf::Vector2f(width / 4 + (width / 2 - nameText.getGlobalBounds().width) / 2, 15 * height / 32 + (height / 16 - nameText.getGlobalBounds().height) / 2));

			}
		}
		win.clear(colours::cinereous);
		win.draw(textInpRect);
		win.draw(nameText);
		win.draw(helpText);
		win.draw(exitButton);
		win.draw(exitText);
		win.display();
	}

	return std::string();
}

bool happyChooser(sf::RenderWindow& win, std::string name, std::string classStr, std::string race)
{

	return true;
}
