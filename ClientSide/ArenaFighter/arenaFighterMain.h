#pragma once
#include<SFML/Graphics.hpp>
#include "../Entities/Characters/character.h"
void createArenaLayout();

void runArenaFighterSingle(sf::RenderWindow &win);

void runArenaFighterMulti(sf::RenderWindow& win);

std::string singleArenaGameloop(sf::RenderWindow& win, character& player, std::vector<std::vector<std::vector<sf::Texture>>> Textures);

std::string multiArenaGameloop(sf::RenderWindow& win, character& player, std::vector<std::vector<std::vector<sf::Texture>>> Textures);