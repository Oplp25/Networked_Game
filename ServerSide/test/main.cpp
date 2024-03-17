#include<SFML/Network.hpp>
#include<iostream>
using namespace std;

int main() {
	/*
	cout << "Booted" << endl;
	sf::TcpListener listener;
	listener.listen(55001);

	sf::TcpSocket clientSocket;
	listener.accept(clientSocket);
	std::cout << "New client connected: " << clientSocket.getRemoteAddress() << std::endl;

	char buffer[1024];
	std::size_t received = 0;
	clientSocket.receive(buffer, sizeof(buffer), received);
	std::cout << "The client said: " << buffer << std::endl;

	clientSocket.send("Hello World",15);

	sf::Packet packet;
	clientSocket.receive(packet);
	string x;
	packet >> x;
	std::cout << "The client said: " << x << std::endl;
	cin >> x;
	*/
	return 0;
}