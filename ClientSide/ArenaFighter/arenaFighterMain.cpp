#include<random>
#include<vector>
#include<filesystem>
#include "arenaFighterMain.h"
#include "../CharacterCreator/characterCreator.h"
#include "../GraphicsFunctions/Colours/colourConsts.h"
#include "../Behavior/Player/playerBehavior.h"
#include "../Entities/Enemies/enemyTemplates.h"
//#include "../GraphicsFunctions/textureLoaders/textureLoaders.h"
using namespace std;
const filesystem::path cwd = filesystem::current_path();
void createArenaLayout()
{
}

void runArenaFighterSingle(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);
	//layout = createArenaLayout()
	sf::Vector2f starter = sf::Vector2f(500, 500);
	sf::Vector2f origin = sf::Vector2f(0, 0);
	enemy x = enemy(orcSwordsman, starter, origin);
	vector<enemy> enemyArrayP = {x};//Will be created by createArenaLayout, but for now will just be manually added
	vector<character> charsArrayP = {};//list of the AI controlled characters
	string result = singleArenaGameloop(win,playerCharacter, charsArrayP, enemyArrayP);
	if (result == "exit") {
		return void();
	}
}

void runArenaFighterMulti(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);
}

string singleArenaGameloop(sf::RenderWindow& win, character& player, vector<character> charsArray,vector<enemy> enemyArray)
{
	//seting up variables
	bool won = false;
	bool finished = false;
	int spriteChangeCounter = 0;
	int spriteChangeInterval = 9;
	char currentDir = 's';

	//Temporary tile boundaries. tile =1840,1000
	sf::RectangleShape topBoundary(sf::Vector2f(1920,40));
	topBoundary.setPosition(sf::Vector2f(0, 0));
	topBoundary.setFillColor(colours::cinereous);
	sf::RectangleShape bottomBoundary(sf::Vector2f(1920, 40));
	bottomBoundary.setPosition(sf::Vector2f(0, 1040));
	bottomBoundary.setFillColor(colours::cinereous);
	sf::RectangleShape rightBoundary(sf::Vector2f(40, 1080));
	rightBoundary.setPosition(sf::Vector2f(1880, 0));
	rightBoundary.setFillColor(colours::cinereous);
	sf::RectangleShape leftBoundary(sf::Vector2f(40, 1080));
	leftBoundary.setPosition(sf::Vector2f(0, 0));
	leftBoundary.setFillColor(colours::cinereous);
	while (!finished) {
		//player graphics
		currentDir = playerBehavior(win, player);
		if (currentDir == 'e') {
			return "exit";
		}
		if (currentDir == 's') {
			player.changeSpriteText("still");
		}
		if (spriteChangeCounter == spriteChangeInterval){
			if (currentDir == 'l') {
				player.changeSpriteText("left");
			}
			else if (currentDir == 'r') {
				player.changeSpriteText("right");
			}
			else if (currentDir == 'u') {
				player.changeSpriteText("up");
			}
			else if (currentDir == 'd') {
				player.changeSpriteText("down");
			}
			player.changeSpriteText("next");
		}

		sf::Event event;
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				win.close();
				return "exit";
			}
		}

		//AI character behavior
		for (character i : charsArray) {
			//currentDir = characterBehavior(i);
			if (currentDir == 's') {
				i.changeSpriteText("still");
			}
			if (spriteChangeCounter == spriteChangeInterval) {
				if (currentDir == 'l') {
					i.changeSpriteText("left");
				}
				else if (currentDir == 'r') {
					i.changeSpriteText("right");
				}
				else if (currentDir == 'u') {
					i.changeSpriteText("up");
				}
				else if (currentDir == 'd') {
					i.changeSpriteText("down");
				}
				i.changeSpriteText("next");
			}
			i.sprite.setPosition(i.localPosition);
			i.currentWeapon.sprite.setPosition(i.localPosition);
		}

		//enemy graphics
		for (enemy i : enemyArray) {
			if (i.tile == player.tile) {
				currentDir = i.behavior(player);
				if (currentDir == 's') {
					i.changeSpriteText("still");
				}
				if (spriteChangeCounter == spriteChangeInterval) {
					if (currentDir == 'l') {
						i.changeSpriteText("left");
					}
					else if (currentDir == 'r') {
						i.changeSpriteText("right");
					}
					else if (currentDir == 'u') {
						i.changeSpriteText("up");
					}
					else if (currentDir == 'd') {
						i.changeSpriteText("down");
					}
					i.changeSpriteText("next");
				}
			}
		}

		//drawing graphics
		win.clear(colours::hunterGreen);
		//Draw background
		win.draw(topBoundary);
		win.draw(bottomBoundary);
		win.draw(rightBoundary);
		win.draw(leftBoundary);

		win.draw(player.draw());
		win.draw(player.currentWeapon.draw());
		for (character i : charsArray) {
			win.draw(i.draw());
			win.draw(i.currentWeapon.draw());
		}
		for (enemy i : enemyArray) {
			if (i.tile == player.tile) {
				win.draw(i.draw());//not working
			}
				
		}
		win.display();
		spriteChangeCounter++;
		if (spriteChangeCounter > spriteChangeInterval) {
			spriteChangeCounter = 0;
		}
	}
	return string();
}

string multiArenaGameloop(sf::RenderWindow& win, character& player, vector<vector<vector<sf::Texture>>> textures)
{
	return string();
}