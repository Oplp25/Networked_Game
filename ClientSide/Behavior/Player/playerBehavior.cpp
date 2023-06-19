#include "playerBehavior.h"

using namespace std;

vector<string> getPlayerInput(sf::RenderWindow& win) {
	vector<string> inputs;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		inputs.push_back("w");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		inputs.push_back("a");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		inputs.push_back("s");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		inputs.push_back("d");
	}
	sf::Event event;
	while (win.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Q) {
				inputs.push_back("q");
			}
			if (event.key.code == sf::Keyboard::R) {
				inputs.push_back("r");
			}
			if (event.key.code == sf::Keyboard::T) {
				inputs.push_back("t");
			}
			if (event.key.code == sf::Keyboard::E) {
				inputs.push_back("e");
			}
			if (event.key.code == sf::Keyboard::LShift) {
				inputs.push_back("shift");
			}
			if (event.key.code == sf::Keyboard::LControl) {
				inputs.push_back("control");
			}
			if (event.key.code == sf::Keyboard::Escape) {
				inputs.push_back("esc");
			}
		}
	}
	return inputs;
}

char playerBehavior(sf::RenderWindow& win, character& player) {
	vector<string> inputs = getPlayerInput(win);
	for (string i : inputs) {
		if (i == "w") {
			player.move('u');
		}if (i == "a") {
			player.move('l');
		}if (i == "s") {
			player.move('d');
		}if (i == "d") {
			player.move('r');
		}if (i == "esc") {
			win.close();
			return 'e';
		}
	}
	if (std::count(inputs.begin(), inputs.end(), "d")!=0) {
		return 'r';
	}
	else if (std::count(inputs.begin(), inputs.end(), "a") != 0) {
		return 'l';
	}
	else if (std::count(inputs.begin(), inputs.end(), "s") != 0){
		return 'd';
	}
	else if (std::count(inputs.begin(), inputs.end(), "w") != 0) {
		return 'u';
	}
	else {
		return 's';
	}
}