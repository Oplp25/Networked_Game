#include "serverConnection.h"
#include<future>
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;

void connectToServerThreaded(promise<bool>) {
	cout << "Reconnecting..." << endl;
}
bool connectToServer(sf::RenderWindow &win) {
	cout << "Reconnecting..." << endl;
	return false;
}