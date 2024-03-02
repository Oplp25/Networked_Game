#pragma once
#include<SFML/Graphics.hpp>

class node {
	private:
	public:
		node(std::vector<int> connectionsP, sf::Vector2f posP);
		node();
		sf::Vector2f pos;
		std::vector<sf::Vector2f> connections;//list of positions in maze that this node is connected to
};