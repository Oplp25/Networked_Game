#pragma once
#include<SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include "../Entities/Characters/character.h"
#include "../Entities/Characters/Classes/classIncluder.h"
#include "../Entities/Characters/Races/raceIncluder.h"


character characterCreator(sf::RenderWindow &win);
std::string classPicker(sf::RenderWindow& win);
std::string racePicker(sf::RenderWindow& win, std::string classStr);
std::string nameChooser(sf::RenderWindow& win);
bool happyChooser(sf::RenderWindow& win, std::string name, std::string classStr, std::string race);
struct spriteComp {
	bool operator()(const sf::Sprite& a, const sf::Sprite& b)const;
};