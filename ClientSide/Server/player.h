#pragma once

#include<SFML/Network.hpp>

#include "../Entities/Characters/character.h"

class player {
	private:
		sf::TcpSocket socket;
	public:
		character playerChar;
		bool sendMessage(std::string message);
		sf::TcpSocket& accessSocket();
		player();
		std::string recieveMessage();
};