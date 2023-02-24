#pragma once
#include<SFML/Graphics.hpp>
void createArenaLayout();

void runArenaFighterSingle(sf::RenderWindow &win);

void runArenaFighterMulti(sf::RenderWindow& win);

void singleArenaGameloop();

void multiArenaGameloop();