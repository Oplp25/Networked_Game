#include<random>
#include<vector>
#include<filesystem>
#include "arenaFighterMain.h"
#include "../CharacterCreator/characterCreator.h"
#include "../GraphicsFunctions/Colours/colourConsts.h"
#include "../Behavior/Player/playerBehavior.h"
#include "../GraphicsFunctions/textureLoaders/textureLoaders.h"
using namespace std;
const filesystem::path cwd = filesystem::current_path();
void createArenaLayout()
{
}

void runArenaFighterSingle(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);
	//layout = createArenaLayout()

	vector<vector<vector<sf::Texture>>> Textures = loadTextures(playerCharacter);//Character, Weapons, Terrain, Items
	vector<vector<vector<sf::Texture>>> otherCharacterTextures = loadOtherCharacterTextures({});
	vector<vector<vector<sf::Texture>>> enemyTextures;
	
	vector<vector<vector<vector<sf::Texture>>>> allTextures = { Textures, otherCharacterTextures, enemyTextures };
	string result = singleArenaGameloop(win,playerCharacter,allTextures);
	if (result == "exit") {
		return void();
	}
}

void runArenaFighterMulti(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);
}

string singleArenaGameloop(sf::RenderWindow& win, character& player, vector<vector<vector<vector<sf::Texture>>>> textures)
{
	bool won = false;
	bool finished = false;
	int spriteNum = 0;
	int spriteChangeCounter = 0;
	char currentDir;
	sf::Sprite playerSprite = sf::Sprite(textures[0][0][4][0]);
	while (!finished) {
		currentDir = playerBehavior(win, player);
		if (currentDir == 'e') {
			return "exit";
		}
		if (currentDir == 's') {
			playerSprite.setTexture(textures[0][0][4][0]);
		}
		if (spriteChangeCounter == 10){
			if (currentDir == 'l') {
				playerSprite.setTexture(textures[0][0][0][spriteNum]);
			}
			else if (currentDir == 'r') {
				playerSprite.setTexture(textures[0][0][1][spriteNum]);
			}
			spriteChangeCounter = -1;
		}
		playerSprite.setPosition(player.localPosition);
		win.clear(colours::hunterGreen);
		win.draw(playerSprite);
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
}

string multiArenaGameloop(sf::RenderWindow& win, character& player, vector<vector<vector<sf::Texture>>> textures)
{
	return string();
}