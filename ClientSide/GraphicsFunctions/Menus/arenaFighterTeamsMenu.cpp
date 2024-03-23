#include "arenaFighterTeamsMenu.h"
#include "../Colours/colourConsts.h"
#include "../../ArenaFighterTeams/arenaFighterTeamsMain.h"
using namespace std;
const filesystem::path cwd = filesystem::current_path();

void runArenaFighterTeamsMenu(sf::RenderWindow& win) {
	int width = win.getSize().x;
	int height = win.getSize().y;
	//setting up font
	sf::Font comicsans;
	if (!comicsans.loadFromFile(cwd.string() + "\\Resources\\Fonts\\ComicSans.ttf")) {
		cout << "Error. Failed to load font Comic Sans" << endl;
	}
	//title text
	sf::Text titleText = sf::Text("Arena Fighter Teams", comicsans, 120);
	titleText.setPosition((width-titleText.getLocalBounds().width)/2,height/16);
	titleText.setFillColor(sf::Color(0,0,0));

	//Setting up the button for singleplayer 
	sf::RectangleShape singleShape = sf::RectangleShape(sf::Vector2f(width-width/4,height/8));
	singleShape.setPosition(sf::Vector2f(width/8, 4 * (height / 8)));
	singleShape.setFillColor(colours::cinereous);
	button singleButton(runArenaFighterTeamsSingle,singleShape);
	sf::Text singleText = sf::Text("Singleplayer",comicsans,90);
	singleText.setPosition(sf::Vector2f(singleShape.getPosition().x + (singleShape.getLocalBounds().width - singleText.getLocalBounds().width) / 2, singleShape.getPosition().y + (singleShape.getLocalBounds().height - singleText.getLocalBounds().height) / 4));
	singleText.setFillColor(sf::Color(0, 0, 0));

	//Setting up the button for multiplayer
	sf::RectangleShape multiShape = sf::RectangleShape(sf::Vector2f(width - width / 4, height / 8));
	multiShape.setPosition(sf::Vector2f(width / 8, 6 * (height / 8)));
	multiShape.setFillColor(colours::cinereous);
	button multiButton(runArenaFighterTeamsMulti, multiShape);
	sf::Text multiText = sf::Text("Multiplayer", comicsans, 90);
	multiText.setPosition(sf::Vector2f(multiShape.getPosition().x+ (multiShape.getLocalBounds().width - multiText.getLocalBounds().width) / 2, multiShape.getPosition().y + (multiShape.getLocalBounds().height - multiText.getLocalBounds().height) / 4));
	multiText.setFillColor(sf::Color(0, 0, 0));

	//arrays
	vector<button> buttonList = {singleButton, multiButton};
	vector<sf::Sprite> spriteList;
	vector<sf::RectangleShape> rectShapeList = { singleShape, multiShape };
	vector<sf::Text> textList = { titleText, singleText, multiText };
	sf::Event event;

	bool run = true;
	while (run) {
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {// if x in corner of window clicked or escape pressed
				win.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mouseLoc = sf::Mouse::getPosition();
				sf::Vector2f mouseLocF = sf::Vector2f(mouseLoc.x, mouseLoc.y);//convert to floats
				for (button i : buttonList) {//iterate over the buttons
					if (i.hitbox.contains(mouseLocF)) {//if clicked on that button
						i.fncPtr(win,socket);//run that buttons function
						run = false;
					}
				}
			}
		}
		win.clear(colours::pistachio);
		for (sf::RectangleShape i : rectShapeList) {
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
