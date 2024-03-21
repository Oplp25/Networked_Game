#include "lobby.h"

lobby::lobby() {
	for(int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			backgroundRectsArray[i][j] = std::vector<sf::RectangleShape>();
			collisionRectsArray[i][j] = std::vector<std::vector<int>>();
		}
	}
}

player& lobby::accessPlayer(int playerNumber)
{
	return playerList[playerNumber];
}
