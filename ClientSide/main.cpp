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

#include "GraphicsFunctions/Intro/intro.h"
#include "GraphicsFunctions/Menus/menu.h"
#include "ConnectionFunctions/serverConnection.h"

using namespace std;


int main() {
	sf::RenderWindow win(sf::VideoMode(800, 800), "Welcome to the Dungeon",sf::Style::Fullscreen);//the main window

	//promise<bool> serverConProm;
	//future<bool> serverConFut = serverConProm.get_future();

	//thread serverConnectionThread(connectToServerThreaded, serverConProm);

	//runIntro(win);

	//bool online = serverConFut.get();
	bool online = false;
	runMenu(win, online);
	return 0;
}