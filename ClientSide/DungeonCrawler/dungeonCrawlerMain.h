#pragma once
#include<SFML/Graphics.hpp>

void runDungeonCrawlerSingle(sf::RenderWindow& win);

void runDungeonCrawlerMulti(sf::RenderWindow& win);

void createDungeonLevel(int currentLevel);//Will need a return value

void singleGameloop();

void multiGameloop();