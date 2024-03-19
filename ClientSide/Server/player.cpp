#include "player.h"

using namespace std;

player::player() {
	socket.setBlocking(false);
}

sf::TcpSocket& player::accessSocket() {
	return socket;
}

bool player::sendMessage(string message) {
	sf::Packet packet;
	packet << message;
	if (socket.send(packet) == sf::Socket::Done){
		return true;
	}
	return false;
}

std::string player::recieveMessage()
{
	string ret;
	sf::Packet packet;
	if (socket.receive(packet) == sf::Socket::Done) {
		packet >> ret;
		return ret;
	}
	else {
		return "error, packet not recieved";
	}
}