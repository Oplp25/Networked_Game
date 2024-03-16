#pragma once
#include<SFML/Network.hpp>
#include<iostream>
#include<string>

void getConnection(sf::TcpSocket &socket, sf::IpAddress address, int port);

void sendMessage(sf::TcpSocket& socket, std::string message);