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

using namespace std;

int main() {
	sf::RenderWindow win(sf::VideoMode(800, 600), "Welcome to the Dungeon");//the main window
	win.setVerticalSyncEnabled(true);
	sf::Event event;
	while (win.isOpen()) {
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				win.close();
			}
		}
		win.clear(sf::Color::Blue);
		win.display();
	}
	return 0;
}