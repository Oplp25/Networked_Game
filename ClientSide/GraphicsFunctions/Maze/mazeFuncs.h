#pragma once
#include<vector>
#include<string>
#include "mazeGraph.h"
#include "cell.h"

 
std::vector<std::vector<cell>> mazeGen();

mazeGraph genGraph();//returns the mazeGraph of a newly generated maze

std::vector<sf::RectangleShape> getCellRects(sf::Vector2f pos,std::vector < sf::Vector2f > conns, sf::RenderWindow& win);

std::vector<sf::RectangleShape> getCellRectsServer(sf::Vector2f pos, std::vector < sf::Vector2f > conns);

std::vector<std::vector<int>> getCollisionRectangles(std::vector<sf::RectangleShape> backRects);

sf::Vector2f checkMoveTile(sf::Vector2f charPos, node currNode, std::vector<int> backgroundDimensions);