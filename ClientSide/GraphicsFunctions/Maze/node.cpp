#include "node.h"

node::node(std::vector<int> connectionsP,sf::Vector2i posP)
{
	pos = posP;
	for (int i : connectionsP) {//connectionsP is a vector of directions
		if (i == 1) {
			connections.push_back(sf::Vector2i(pos.x,pos.y-1));
		}else if (i == 2) {
			connections.push_back(sf::Vector2i(pos.x+1, pos.y));
		}else if (i == 3) {
			connections.push_back(sf::Vector2i(pos.x, pos.y+1));
		}else if (i == 4) {
			connections.push_back(sf::Vector2i(pos.x-1, pos.y));
		}
	}
}
node::node() {
	connections = {};
	pos = sf::Vector2i(-1, -1);
}