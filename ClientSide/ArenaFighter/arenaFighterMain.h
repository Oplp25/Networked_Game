#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include "../Entities/Characters/character.h"
#include "../Entities/Enemies/enemy.h"
#include "../GraphicsFunctions/Maze/mazeGraph.h"
mazeGraph createArenaLayout();//create the maze and populate it

void runArenaFighterSingle(sf::RenderWindow &win, sf::TcpSocket& socket);//run the singleplayer version

void runArenaFighterMulti(sf::RenderWindow& win, sf::TcpSocket& socket);//run the multiplayer variant

std::string singleArenaGameloop(sf::RenderWindow& win, character& player, std::vector<character> charArray, std::vector<enemy> enemyArray, mazeGraph currentMazeGraph);//gameloop for the singleplayer version

std::string multiArenaGameloop(sf::RenderWindow& win, character& player);//game loop for the multiplayer version