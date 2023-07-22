#pragma once
#include<SFML/Graphics.hpp>
#include "../Entities/Characters/character.h"
void createArenaLayout();

void runArenaFighterSingle(sf::RenderWindow &win);

void runArenaFighterMulti(sf::RenderWindow& win);

std::string singleArenaGameloop(sf::RenderWindow& win, character& player, std::vector<character> charArray);

std::string multiArenaGameloop(sf::RenderWindow& win, character& player, std::vector<character> charArray);