#pragma once
#include<SFML/Network.hpp>
#include<iostream>
#include<string>

void getConnection(sf::TcpSocket &socket, std::string address, int port);

void sendMessage(sf::TcpSocket& socket, std::string message);