#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<vector>

#include "../GraphicsFunctions/Maze/mazeGraph.h"
#include "player.h"

class lobby {
	private:
		std::vector<player> playerList;
	public:
		std::vector<enemy> enemyArray;
		bool started;
		int playerCount;
		//Ai character list
		mazeGraph lobbyMaze;
		player& accessPlayer(int playerNumber);
		lobby();
		void startGame();
};