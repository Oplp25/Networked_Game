#include "clientTest.h"

using namespace std;

void getConnection(sf::TcpSocket &socket, std::string address, int port)
{
	sf::Socket::Status status = socket.connect(address, port);
	if (status != sf::Socket::Done){
		cout << "Error. Client could not connect to server." << endl;
		throw std::invalid_argument("Socket could not connect");
	}
}

void sendMessage(sf::TcpSocket& socket, std::string message)
{
	if (socket.send(message.c_str(), message.size()+1) != sf::Socket::Done)
	{
		cout << "Error. Message not sent." << endl;
		throw std::invalid_argument("Message not sent");
	}
}
