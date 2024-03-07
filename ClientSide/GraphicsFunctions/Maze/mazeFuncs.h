#pragma once
#include<vector>
#include<string>
#include "mazeGraph.h"
#include "cell.h"

 
std::vector<std::vector<cell>> mazeGen();

mazeGraph genGraph();//returns the mazeGraph of a newly generated maze

std::vector<sf::RectangleShape> getCellRects(sf::Vector2f pos,std::vector < sf::Vector2f > conns, sf::RenderWindow& win);

std::vector<std::vector<int>> getCollisionRectangles(std::vector<sf::RectangleShape> backRects);