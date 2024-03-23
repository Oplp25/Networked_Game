#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
void runArenaFighterTeamsSingle(sf::RenderWindow& win, sf::TcpSocket& socket);//run the single player version

void runArenaFighterTeamsMulti(sf::RenderWindow& win, sf::TcpSocket& socket);//run the multiplayer version

void createArenaLevel(int currentLevel);//create the level

void singleArenaGameloop();

void multiArenaGameloop();