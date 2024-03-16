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


#include "testFolder(Temp)/clientTest.h"
using namespace std;


int main() {

	sf::TcpSocket socket;

	getConnection(socket,sf::IpAddress::getLocalAddress(), 55001);

	sendMessage(socket, "Hello World");

	char buffer[1024];
	std::size_t received = 0;
	socket.receive(buffer, sizeof(buffer), received);
	std::cout << "The server said: " << buffer << std::endl;

	sendPacket(socket,"Packets are cool");
	int x;
	cin >> x;

	/*
	sf::RenderWindow win(sf::VideoMode(1920, 1080), "Welcome to the Arena");//the main window
	//sf::RenderWindow win(sf::VideoMode(1920, 1080), "Welcome to the Arena",sf::Style::Fullscreen);
	win.setFramerateLimit(60);
	//promise<bool> serverConProm;
	//future<bool> serverConFut = serverConProm.get_future();

	//thread serverConnectionThread(connectToServerThreaded, serverConProm);

	//runIntro(win);

	//bool online = serverConFut.get();
	bool online = false;
	runMenu(win, online);
	*/
	return 0;
}