#pragma once

#include<SFML/Network.hpp>

class player {
	private:
		sf::TcpSocket socket;
	public:
		//character playerChar;
		bool setConnection();
		bool sendMessage(std::string message);
		player();
};