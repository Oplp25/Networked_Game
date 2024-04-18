#include "clientTest.h"

using namespace std;

void getConnection(sf::TcpSocket &socket, sf::IpAddress address , int port)
{
	sf::Socket::Status status = socket.connect(address, port);// attempts to connect to port port at IP address address
	if (status != sf::Socket::Done){//If it failed
		cout << "Error. Client could not connect to server." << endl;
		throw std::invalid_argument("Socket could not connect");
	}
}

void sendMessage(sf::TcpSocket& socket, std::string message)
{
	if (socket.send(message.c_str(), message.size()+1) != sf::Socket::Done)//converts message to a C-type string. Also have to pass the size of the message being sent.
	{
		//if it failed
		cout << "Error. Message not sent." << endl;
		throw std::invalid_argument("Message not sent");
	}
}

void sendPacket(sf::TcpSocket& socket, std::string message) {
	sf::Packet packet;

	packet << message;

	if (socket.send(packet) != sf::Socket::Done)
	{
		cout << "Error. Message not sent." << endl;
		throw std::invalid_argument("Message not sent");
	}
}