#include<random>
#include<vector>
#include<filesystem>
#include "arenaFighterMain.h"
#include "../CharacterCreator/characterCreator.h"
#include "../GraphicsFunctions/Colours/colourConsts.h"
#include "../Behavior/Player/playerBehavior.h"
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
	vector<character> charsArray = {};//list of the AI controlled characters
	string result = singleArenaGameloop(win,playerCharacter, charsArray);
	if (result == "exit") {
		return void();
	}
}

void runArenaFighterMulti(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);
}

string singleArenaGameloop(sf::RenderWindow& win, character& player, vector<character> charsArray)
{
	//seting up variables
	bool won = false;
	bool finished = false;
	int spriteChangeCounter = 0;
	int spriteChangeInterval = 9;
	char currentDir = 's';
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
		player.sprite.setPosition(player.localPosition);
		player.currentWeapon.sprite.setPosition(player.localPosition);

		sf::Event event;
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				win.close();
				return "exit";
			}
		}

		//AI character graphics
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


		//other graphics
		win.clear(colours::hunterGreen);
		win.draw(player.draw());
		win.draw(player.currentWeapon.draw());
		for (character i : charsArray) {
			win.draw(i.draw());
			win.draw(i.currentWeapon.draw());
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