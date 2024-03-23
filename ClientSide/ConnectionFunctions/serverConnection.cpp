#include "serverConnection.h"
#include<future>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>

using namespace std;

void connectToServerThreaded(promise<sf::Socket::Status> prom, sf::TcpSocket& socket, sf::IpAddress address, int port) {
	sf::Socket::Status status = socket.connect(address, port);
	prom.set_value(status);
}

bool connectToServer(sf::TcpSocket& socket, sf::IpAddress address, int port)
{
	sf::Socket::Status status  = socket.connect(address, port);
	if (status == sf::Socket::Done) {
		return true;
	}
	return false;
}
