#pragma once
#include<SFML/Graphics.hpp>
#include<future>

void connectToServerThreaded(std::promise<bool>);//connects to the server in its own thread
bool connectToServer(sf::RenderWindow &win);