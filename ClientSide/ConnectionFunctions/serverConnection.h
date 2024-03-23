#pragma once
#include<SFML/Graphics.hpp>
#include<future>

void connectToServerThreaded(std::promise<sf::Socket::Status> prom, sf::TcpSocket& socket, sf::IpAddress address, int port);//connects to the server in its own thread
bool connectToServer(sf::TcpSocket& socket, sf::IpAddress address, int port);