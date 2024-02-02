#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>
#include <fcntl.h>
#include<SFML/Graphics.hpp>


const std::vector<std::string> cellTypes = { "h2","h3d","h3u","c1","c2","c3","c4","h4","v2","v3r","v3l" };
const std::vector<std::vector<int>> combos = { {1,2},{1,3},{1,4},{2,3},{2,4},{3,4},{1,2,3},{1,2,4},{1,3,4},{2,3,4},{1,2,3,4} };
const std::vector<std::vector<int>> order = { {2,3},{1,3},{1,2},{1,1},{2,1},{3,1},{3,2},{3,3},{3,4},{2,4},{1,4},{0,4},{0,3},{0,2},{0,1},{0,0},{1,0},{2,0},{3,0},{4,0},{4,1},{4,2},{4,3},{4,4} };



class cell{
    private:
    public:
        std::vector<int> conns;// 1-up, 2-right, 3-down, 4-left
        sf::Vector2f pos;//sf::vector2f pos;
        std::string cellType;
        std::string draw(int i);
        std::string genNewCell(int relation);
        cell(std::string cType, sf::Vector2f posP);
        cell();
};