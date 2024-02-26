#pragma once
#include<SFML/Graphics.hpp>

class node {
	private:
	public:
		node(std::vector<int> connectionsP, sf::Vector2i posP);
		node();
		sf::Vector2i pos;
		std::vector<sf::Vector2i> connections;//list of positions in maze that this node is connected to
};