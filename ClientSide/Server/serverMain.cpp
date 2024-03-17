#include "serverMain.h"

#include<SFML/Network.hpp>
#include<iostream>

#include "lobby.h"

using namespace std;

int runServer() {

	cout << "Booted" << endl;
	sf::TcpListener listener;
	listener.listen(55001);

	bool run = true;
	vector<lobby> lobbyList = { lobby() };
	int currLobbySize = 0;
	while (run){
		listener.accept(lobbyList[lobbyList.size()-1].accessPlayer(currLobbySize).accessSocket());
	}
	/*
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