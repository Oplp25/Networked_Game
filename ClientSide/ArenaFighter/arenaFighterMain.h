#pragma once
#include<SFML/Graphics.hpp>
#include "../Entities/Characters/character.h"
#include "../Entities/Enemies/enemy.h"
void createArenaLayout();

void runArenaFighterSingle(sf::RenderWindow &win);

void runArenaFighterMulti(sf::RenderWindow& win);

std::string singleArenaGameloop(sf::RenderWindow& win, character& player, std::vector<character> charArray, std::vector<enemy> enemyArray);

std::string multiArenaGameloop(sf::RenderWindow& win, character& player, std::vector<character> charArray);