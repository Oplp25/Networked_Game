#include "serverMain.h"

#include<SFML/Network.hpp>
#include<iostream>
#include<thread>

#include "lobby.h"
#include "../GraphicsFunctions/Maze/mazeFuncs.h"

using namespace std;

int runServer() {

	cout << "Booted" << endl;
	sf::TcpListener listener;
	listener.listen(55001);

	bool run = true;
	vector<lobby> lobbyList = { lobby() };
	int currLobbySize = 0;
	lobbyList[0].lobbyMaze = genGraph();
	while (run){
		if (listener.accept(lobbyList[lobbyList.size() - 1].accessPlayer(currLobbySize).accessSocket()) == sf::Socket::Done) {
			currLobbySize++;
			if (currLobbySize == 8) {
				lobbyList[lobbyList.size() - 1].startGame();
				lobbyList.push_back(lobby());
				lobbyList[lobbyList.size() - 1].lobbyMaze = genGraph();
			}
		}
		for (lobby i : lobbyList) {
			if (i.started) {
				tickGame(i);
			}
			else {
				if (updatePreGameLobby(i)) {
					i.startGame();
				}
			}
		}

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


void tickGame(lobby toTick) {
	
}

bool updatePreGameLobby(lobby toTick){
	return false;
}
