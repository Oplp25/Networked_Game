#pragma once
#include<SFML/Graphics.hpp>
#include<future>

void connectToServerThreaded(std::promise<bool>);
bool connectToServer(sf::RenderWindow &win);