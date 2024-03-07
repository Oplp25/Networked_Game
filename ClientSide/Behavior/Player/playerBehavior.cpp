#include "playerBehavior.h"
#include <chrono>
#include<thread>
using namespace std;

vector<string> getPlayerInput(sf::RenderWindow& win) {
	vector<string> inputs;

	//For buttons that need to be held down
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

	//For buttons that are pressed once
	sf::Event event;
	while (win.pollEvent(event)) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				inputs.push_back("mLeft");
			}
			if (event.mouseButton.button == sf::Mouse::Right) {
				inputs.push_back("mRight");
			}

		}
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
			if (event.key.code == sf::Keyboard::F) {
				inputs.push_back("f");
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
			if (event.key.code == sf::Keyboard::Space) {
				inputs.push_back("space");
			}
		}
	}
	return inputs;
}

char playerBehavior(sf::RenderWindow& win, character& player, vector<enemy> &enemyArray, vector<vector<sf::Vector2f*>> collObjs, vector<sf::RectangleShape> tileLayout) {
	vector<string> inputs = getPlayerInput(win);
	for (string i : inputs) {
		if (i == "w") {
			player.move('u',collObjs, tileLayout);
		}if (i == "a") {
			player.move('l', collObjs, tileLayout);
		}if (i == "s") {
			player.move('d', collObjs, tileLayout);
		}if (i == "d") {
			player.move('r', collObjs, tileLayout);
		}if (i == "esc") {
			win.close();
			return 'e';
		}

		//pause
		if (i == "space") {
			this_thread::sleep_for(chrono::milliseconds(500));
			int do_nothing = 0;
			while (true) {
				do_nothing++;
				if (do_nothing > 7) {
					do_nothing = 0;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					break;
				}
			}
		}

		if (i == "mLeft" && !player.attacking) {
			player.usePrimary(enemyArray);
		}
		/*
		if (i == "mRight") {
			player.useSecondary();
		}
		if (i == "e") {
			player.useSpecial();
		}
		if (i == "q") {
			player.useBuff();
		}
		if (i == "f") {
			player.useDefensive();
		}
		if (i == "r") {
			player.useUlt();
		}*/
	}

	
	if (std::count(inputs.begin(), inputs.end(), "d")!=0) {// if "d" in inputs 
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