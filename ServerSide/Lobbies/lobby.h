#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<vector>

#include "player.h"

class lobby {
public:
	int playerCount;
private:
	std::vector<player> playerList;
};