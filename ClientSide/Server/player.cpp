#include "player.h"

#include "packetOverrides.h"

using namespace std;

player::player() {
	socket.setBlocking(false);
	currentDir = 's';
	message = "";
}

sf::TcpSocket& player::accessSocket() {
	return socket;
}

bool player::sendPreparedMessage() {
	sf::Packet packet;
	packet << message;
	if (socket.send(packet) == sf::Socket::Done){
		return true;
	}
	return false;
}

bool player::sendMessage(entity& toSend) {
	sf::Packet packet;
	packet << toSend;
	if (socket.send(packet) == sf::Socket::Done) {
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

void player::addToMessage(string toAdd) {
	message += ";" + toAdd;
}