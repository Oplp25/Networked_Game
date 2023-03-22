#include "CharacterCreator.h"

using namespace std;

character characterCreator(sf::RenderWindow& win)
{
	bool happy = false;
	character myChar;
	while (!happy) {
		string classChoiceString = classPicker(win);
		string raceChoiceString = racePicker(win);
		myChar = character(raceChoiceString,classChoiceString,"name");
		happy = true;
	}
	return myChar;
}

std::string classPicker(sf::RenderWindow& win)
{
	return std::string();
}

std::string racePicker(sf::RenderWindow& win)
{
	return std::string();
}

std::string nameChooser(sf::RenderWindow& win)
{
	return std::string();
}
