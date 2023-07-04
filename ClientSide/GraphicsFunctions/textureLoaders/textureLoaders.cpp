#include "textureLoaders.h"

using namespace std;

std::vector<std::vector<std::vector<sf::Texture>>> loadOtherCharacterTextures(std::vector<character> characterList)
{
	return std::vector<std::vector<std::vector<sf::Texture>>>();
}

std::vector<std::vector<std::vector<sf::Texture>>> loadTextures(character myChar)
{
	std::vector<std::vector<std::vector<sf::Texture>>> textures = { characterTextureLoader(myChar), weaponTextureLoader()};
		return textures;
}

std::vector<std::vector<std::vector<sf::Texture>>> loadEnemyTextures()
{
	return std::vector<std::vector<std::vector<sf::Texture>>>();
}

std::vector<std::vector<sf::Texture>> characterTextureLoader(character aCharacter)//Left, Right, Up, Down, Misc
{
	const filesystem::path cwd = filesystem::current_path();
	vector<sf::Texture> characterLeft;
	for (int i = 1; i < 10; i++) {
		characterLeft.push_back(sf::Texture());
		if (!characterLeft.back().loadFromFile(cwd.string() + "/Resources/Sprite Assets/" + aCharacter.characterRace + " " + aCharacter.className + "/L" + to_string(i) + ".png")) {
			cout << "Error: Failed to load \"" << "L" + to_string(i) + ".png\" from file" << endl;
			sf::Texture t;
			t.create(120, 120);
			characterLeft.back() = t;
		}
	}
	vector<sf::Texture> characterRight;
	for (int i = 1; i < 10; i++) {
		characterRight.push_back(sf::Texture());
		if (!characterRight.back().loadFromFile(cwd.string() + "/Resources/Sprite Assets/" + aCharacter.characterRace + " " + aCharacter.className + "/R" + to_string(i) + ".png")) {
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
	if (!characterStill.loadFromFile(cwd.string() + "/Resources/RaceIcons/" + aCharacter.className + "/" + aCharacter.characterRace + ".png")) {
		cout << "Character image not loaded" << endl;
	}
	characterMisc.push_back(characterStill);

	vector<vector<sf::Texture>> characterTextures = { characterLeft,characterRight,characterUp,characterDown,characterMisc };//Left, Right, Up, Down, Misc
	return characterTextures;
}

std::vector<std::vector<sf::Texture>> weaponTextureLoader()
{
	const filesystem::path cwd = filesystem::current_path();
	vector<vector<sf::Texture>> weaponsTextures;
	string path = cwd.string() + "\Resources\Sprite Assets\Weapons\\";
	vector<sf::Texture> tempVect;
	for (string i : iWeapons) {
		tempVect = {sf::Texture(),sf::Texture()};
		if (!tempVect[0].loadFromFile(path + i + ".png"));
		if (!tempVect[1].loadFromFile(path + i + "NoHandle.png"));
		weaponsTextures.push_back(tempVect);
	}
	return std::vector<std::vector<sf::Texture>>();
}
