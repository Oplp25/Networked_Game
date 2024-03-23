#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<vector>
#include<random>
#include<filesystem>
#include<thread>
#include<chrono>
#include<future>
#include<format>
#include "SQlite/sqlite3.h"

#include "GraphicsFunctions/Maze/mazeGraph.h"
#include "GraphicsFunctions/Maze/mazeFuncs.h"

#include "GraphicsFunctions/Intro/intro.h"
#include "GraphicsFunctions/Menus/menu.h"
#include "ConnectionFunctions/serverConnection.h"

#include "Server/serverMain.h"

#include "testFolder(Temp)/clientTest.h"
using namespace std;


int main() {
	/*
	sf::TcpSocket socket;


	//use this if testing on one computer
	//getConnection(socket,sf::IpAddress::getLocalAddress(), 55001);


	//use this if connecting over a LAN
	sf::IpAddress address("Jakob_PC");//change IP address each time
	getConnection(socket, address, 55001);
	sendMessage(socket, "Hello World");

	char buffer[1024];
	std::size_t received = 0;
	socket.receive(buffer, sizeof(buffer), received);
	std::cout << "The server said: " << buffer << std::endl;

	sendPacket(socket,"Packets are cool");
	int x;
	cin >> x;
	*/
	

	cout << "Client(c) or Server(s)?" << endl;
	string s;
	cin >> s;

	if (s[0] == 's') {
		runServer();
		return 0;
	}
	else if (s[0] == 't') {
		sf::TcpSocket socket;


		//use this if testing on one computer
		//getConnection(socket,sf::IpAddress::getLocalAddress(), 55001);


		//use this if connecting over a LAN
		sf::IpAddress address("Jakob_PC");//change IP address each time
		getConnection(socket, address, 55001);
		sendMessage(socket, "Hello World");

		char buffer[1024];
		std::size_t received = 0;
		socket.receive(buffer, sizeof(buffer), received);
		std::cout << "The server said: " << buffer << std::endl;

		sendPacket(socket, "Packets are cool");
		int x;
		cin >> x;
		return 0;
	}
	sf::TcpSocket socket;

	sf::RenderWindow win(sf::VideoMode(1920, 1080), "Welcome to the Arena");//the main window
	//sf::RenderWindow win(sf::VideoMode(1920, 1080), "Welcome to the Arena",sf::Style::Fullscreen);
	
	win.setFramerateLimit(60);
	promise<sf::Socket::Status> serverConProm;
	future<sf::Socket::Status> serverConFut = serverConProm.get_future();

	thread serverConnectionThread(connectToServerThreaded, serverConProm);

	runIntro(win);

	sf::Socket::Status online = serverConFut.get();
	serverConnectionThread.join();
	runMenu(win, online);
	return 0;
}