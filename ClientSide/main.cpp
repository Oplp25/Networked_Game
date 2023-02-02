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
#include <format>
#include "SQlite/sqlite3.h"

#include "GraphicsFunctions/Intro/intro.h"
#include "GraphicsFunctions/Menus/menu.h"

using namespace std;

void connectToServer(promise<bool>);

int main() {
	sf::RenderWindow win(sf::VideoMode(800, 800), "Welcome to the Dungeon",sf::Style::Fullscreen);//the main window

	//promise<bool> serverConProm;
	//future<bool> serverConFut = serverConProm.get_future();

	//thread serverConnectionThread(connectToServer, serverConProm);

	runIntro(win);

	//bool online = serverConFut.get();
	
	runMenu(win);
	return 0;
}