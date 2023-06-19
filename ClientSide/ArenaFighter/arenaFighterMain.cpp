#include<random>
#include<vector>
#include<filesystem>
#include "arenaFighterMain.h"
#include "../CharacterCreator/characterCreator.h"
#include "../GraphicsFunctions/Colours/colourConsts.h"
#include "../Behavior/Player/playerBehavior.h"
using namespace std;
const filesystem::path cwd = filesystem::current_path();
void createArenaLayout()
{
}

void runArenaFighterSingle(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);
	//layout = createArenaLayout()
	vector<sf::Texture> characterLeft;
	for (int i = 1; i < 10; i++) {
		characterLeft.push_back(sf::Texture());
		if (!characterLeft.back().loadFromFile(cwd.string() + "/Resources/Sprite Assets/" + playerCharacter.characterRace +" " + playerCharacter.className + "/L" + to_string(i) + ".png")) {
			cout << "Error: Failed to load \"" << "L" + to_string(i) + ".png\" from file" << endl;
			sf::Texture t;
			t.create(120, 120);
			characterLeft.back() = t;
		}
	}
	vector<sf::Texture> characterRight;
	for (int i = 1; i < 10; i++) {
		characterRight.push_back(sf::Texture());
		if (!characterRight.back().loadFromFile(cwd.string() + "/Resources/Sprite Assets/" + playerCharacter.characterRace +" " + playerCharacter.className + "/R" + to_string(i) + ".png")) {
			cout << "Error: Failed to load \"" << "R" + to_string(i) + ".png\" from file" << endl;
			sf::Texture t;
			t.create(120, 120);
			characterRight.back() = t;
		}
	}
	vector<sf::Texture> characterUp;
	vector<sf::Texture> characterDown;
	vector<sf::Texture> characterMisc;
	sf::Texture characterStill;
	if(!characterStill.loadFromFile(cwd.string()+"/Resources/RaceIcons/"+playerCharacter.className+"/"+playerCharacter.characterRace+".png")) {
		cout << "Character image not loaded" << endl;
	}
	characterMisc.push_back(characterStill);

	vector<vector<sf::Texture>> characterTextures = { characterLeft,characterRight,characterUp,characterDown,characterMisc };//Left, Right, Up, Down, Misc
	vector<vector<vector<sf::Texture>>> Textures = { characterTextures };//Character,Terrain, Enemy, Other Characters
	string result = singleArenaGameloop(win,playerCharacter,Textures);
	if (result == "exit") {
		return void();
	}
}

void runArenaFighterMulti(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);
}

string singleArenaGameloop(sf::RenderWindow& win, character& player, vector<vector<vector<sf::Texture>>> textures)
{
	bool won = false;
	bool finished = false;
	int spriteNum = 0;
	int spriteChangeCounter = 0;
	char currentDir;
	sf::Sprite playerSprite = sf::Sprite(textures[0][4][0]);
	while (!finished) {
		currentDir = playerBehavior(win, player);
		if (currentDir == 'e') {
			return "exit";
		}
		if (currentDir == 's') {
			playerSprite.setTexture(textures[0][4][0]);
		}
		if (spriteChangeCounter == 10){
			if (currentDir == 'l') {
				playerSprite.setTexture(textures[0][0][spriteNum]);
			}
			else if (currentDir == 'r') {
				playerSprite.setTexture(textures[0][1][spriteNum]);
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