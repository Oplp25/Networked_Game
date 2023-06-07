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
	vector<sf::Sprite> characterLeft;
	vector<sf::Sprite> characterRight;
	vector<sf::Sprite> characterUp;
	vector<sf::Sprite> characterDown;
	vector<sf::Sprite> characterMisc;
	sf::Texture characterStillText;
	if(!characterStillText.loadFromFile(cwd.string()+"/Resources/RaceIcons/"+playerCharacter.className+"/"+playerCharacter.characterRace+".png")) {
		cout << "Character image not loaded" << endl;
	}
	sf::Sprite characterStill = sf::Sprite(characterStillText);
	characterMisc.push_back(characterStill);

	vector<vector<sf::Sprite>> characterSprites = { characterLeft,characterRight,characterUp,characterDown,characterMisc };//Left, Right, Up, Down, Misc
	vector<vector<vector<sf::Sprite>>> sprites = { characterSprites };//Character,Terrain, Enemy, Other Characters
	string result = singleArenaGameloop(win,playerCharacter,sprites);
	if (result == "exit") {
		return void();
	}
}

void runArenaFighterMulti(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);
}

string singleArenaGameloop(sf::RenderWindow& win, character& player, vector<vector<vector<sf::Sprite>>> sprites)
{
	bool won = false;
	bool finished = false;
	while (!finished) {
		if (!playerBehavior(win, player)) {
			return "exit";
		}
		sprites[0][4][0].setPosition(player.localPosition);
		win.clear(colours::hunterGreen);
		win.draw(sprites[0][4][0]);
		win.display();
	}
	return string();
}

string multiArenaGameloop(sf::RenderWindow& win, character& player, vector<vector<vector<sf::Sprite>>> sprites)
{
	return string();
}