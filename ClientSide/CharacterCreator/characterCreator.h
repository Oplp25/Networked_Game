#pragma once
#include<SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include "../Entities/Characters/character.h"
#include "../Entities/Characters/Classes/classIncluder.h"
#include "../Entities/Characters/Races/raceIncluder.h"

std::vector<std::string> classesList = {"Barbarian" ,"Bard","Cleric","Druid","Fighter","Monk","Paladin","Rogue","Wizard","Artificer"};
character characterCreator(sf::RenderWindow &win);
std::string classPicker(sf::RenderWindow& win);
std::string racePicker(sf::RenderWindow& win);
std::string nameChooser(sf::RenderWindow& win);