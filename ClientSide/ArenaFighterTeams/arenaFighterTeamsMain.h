#pragma once
#include<SFML/Graphics.hpp>

void runArenaFighterTeamsSingle(sf::RenderWindow& win);//run the single player version

void runArenaFighterTeamsMulti(sf::RenderWindow& win);//run the multiplayer version

void createArenaLevel(int currentLevel);//create the level

void singleArenaGameloop();

void multiArenaGameloop();