#pragma once
#include<SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include "../Entities/Characters/character.h"
#include "../Entities/Characters/Classes/classIncluder.h"
#include "../Entities/Characters/Races/raceIncluder.h"


character characterCreator(sf::RenderWindow &win);//character creator function
std::string classPicker(sf::RenderWindow& win);//function to pick class
std::string racePicker(sf::RenderWindow& win, std::string classStr);//function to pick race
std::string nameChooser(sf::RenderWindow& win);//function to pick name
bool happyChooser(sf::RenderWindow& win, std::string name, std::string classStr, std::string race);//function to check if the player is happy with their character
struct spriteComp {//struct to compare 2 different sprites, needed for ordered maps
	bool operator()(const sf::Sprite& a, const sf::Sprite& b)const;
};