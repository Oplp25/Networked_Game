#pragma once

#include<SFML/Network.hpp>

#include "../Entities/Characters/character.h"

class player {
	private:
		sf::TcpSocket socket;
		std::string message;
	public:
		char currentDir;
		character playerChar;
		bool sendPreparedMessage();
		bool sendMessage(entity& toSend);
		void addToMessage(std::string toAdd);
		sf::TcpSocket& accessSocket();
		player();
		std::string recieveMessage();
};