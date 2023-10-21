#pragma once
#include<string>
#include<vector>
#include "../../Entities/Enemies/enemy.h"
#include "../../Entities/Characters/character.h"
std::vector<std::string> getPlayerInput(sf::RenderWindow& win);
char playerBehavior(sf::RenderWindow& win, character& player,std::vector<enemy> &enemyArray);