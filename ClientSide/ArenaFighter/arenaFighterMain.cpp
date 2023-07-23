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
	bool won = false;
	bool finished = false;
	int spriteNum = 0;
	int spriteChangeCounter = 0;
	char currentDir = 's';
	char prevDir = 's';
	while (!finished) {
		prevDir = currentDir;
		currentDir = playerBehavior(win, player);
		if (currentDir == 'e') {
			return "exit";
		}
		if (currentDir == 's') {
			player.changeSpriteText("still");
		}
		if (spriteChangeCounter == 10){
			if (prevDir != currentDir) {
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
			}
			player.changeSpriteText("next");
			spriteChangeCounter = -1;
		}
		player.sprite.setPosition(player.localPosition);
		win.clear(colours::hunterGreen);
		win.draw(player.draw());
		win.display();
		spriteNum++;
		spriteChangeCounter++;
		if (spriteChangeCounter > 10) {
			spriteChangeCounter = 0;
		}
		if (spriteNum >= 9) {
			spriteNum = 0;
		}
	}
	return string();
}

string multiArenaGameloop(sf::RenderWindow& win, character& player, vector<vector<vector<sf::Texture>>> textures)
{
	return string();
}