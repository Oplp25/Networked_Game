#include "serverMain.h"

#include<SFML/Network.hpp>
#include<iostream>
#include<thread>

#include "lobby.h"
#include "../GraphicsFunctions/Maze/mazeFuncs.h"
#include "../Behavior/Player/playerBehavior.h"
#include "packetOverrides.h"
using namespace std;

int runServer() {

	/*cout << "Booted" << endl;
	sf::TcpListener listener;
	listener.listen(55001);

	bool run = true;
	vector<lobby> lobbyList = { lobby() };
	int currLobbySize = 0;
	lobbyList[0].lobbyMaze = genGraph();
	while (run){
		if (listener.accept(lobbyList[lobbyList.size() - 1].accessPlayer(currLobbySize).accessSocket()) == sf::Socket::Done) {
			currLobbySize++;
			if (currLobbySize == 8) {
				lobbyList[lobbyList.size() - 1].startGame();
				lobbyList.push_back(lobby());
				lobbyList[lobbyList.size() - 1].lobbyMaze = genGraph();
			}
		}
		for (lobby i : lobbyList) {
			if (i.started) {
				tickGame(i);
			}
			else {
				if (updatePreGameLobby(i)) {
					i.startGame();
				}
			}
		}

	}*/

	cout << "Booted" << endl;
	sf::TcpListener listener;
	listener.listen(55001);//opens port 55001 and listens for connections attempting to be made
	sf::TcpSocket clientSocket;
	listener.accept(clientSocket);//anything trying to connect gets made into clientSocket
	std::cout << "New client connected: " << clientSocket.getRemoteAddress() << std::endl;//outputs client's IP address

	char buffer[1024];
	std::size_t received = 0;
	clientSocket.receive(buffer, sizeof(buffer), received);// gets message client sent and puts it in the buffer
	std::cout << "The client said: " << buffer << std::endl;

	clientSocket.send("Hello World",15);

	sf::Packet packet;
	clientSocket.receive(packet);
	string x;
	packet >> x;
	std::cout << "The client said: " << x << std::endl;
	cin >> x;
	
	return 0;
}


void tickGame(lobby currentLobby) {
	bool finished = false;
	vector<int> check;
	int spriteChangeCounter = 0;
	int spriteChangeInterval = 12;

	for (int i = 0; i < currentLobby.playerCount; i++) {
		currentLobby.backgroundRectsArray[currentLobby.accessPlayer(i).playerChar.tile.x][currentLobby.accessPlayer(i).playerChar.tile.y] = getCellRectsServer(currentLobby.lobbyMaze.getNode(currentLobby.accessPlayer(i).playerChar.tile).pos, currentLobby.lobbyMaze.getNode(currentLobby.accessPlayer(i).playerChar.tile).connections);
		currentLobby.collisionRectsArray[currentLobby.accessPlayer(i).playerChar.tile.x][currentLobby.accessPlayer(i).playerChar.tile.y] = getCollisionRectangles(currentLobby.backgroundRectsArray[currentLobby.accessPlayer(i).playerChar.tile.x][currentLobby.accessPlayer(i).playerChar.tile.y]);
	}
	vector<vector<sf::Vector2f*>> collObjs;//collision objects. 
	vector<entity&> playerCharArray;
	for (int i = 0; i < currentLobby.playerCount; i++) {
		playerCharArray.push_back(currentLobby.accessPlayer(i).playerChar);
	}
	for (int i = 0; i < currentLobby.enemyArray.size(); i++) {
		collObjs.push_back({ &currentLobby.enemyArray[i].tile, &currentLobby.enemyArray[i].localPosition });//add enemy coords
	}
	//Bot list
	/*for (int i = 0; i < charsArray.size(); i++) {
		collObjs.push_back({ &charsArray[i].tile, &charsArray[i].localPosition });//add bot coords
		}*/
	for (int i = 0; i < currentLobby.playerCount; i++) {
		collObjs.push_back({ &currentLobby.accessPlayer(i).playerChar.tile, &currentLobby.accessPlayer(i).playerChar.localPosition});//add 2 coords
	}

	sf::Vector2f newTile;
	char currentDir;
	while (!finished) {
		//player graphics
		for (int i = 0; i < currentLobby.playerCount; i++) {
			sf::Vector2f curTile = currentLobby.accessPlayer(i).playerChar.tile;
			if (currentLobby.accessPlayer(i).playerChar.hpCurrent <= 0) {//if player is dead
				currentLobby.accessPlayer(i).addToMessage("dead");
			}
			//need to use sockets to get inputs
			//currentLobby.accessPlayer(i).currentDir = playerBehavior(win, player, currentLobby.enemyArray, collObjs, collisionRectangles);//get the direction of motion for the player

			currentDir = 's';
			if (currentDir == 's' && !currentLobby.accessPlayer(i).playerChar.attacking) {
				currentLobby.accessPlayer(i).playerChar.changeSpriteText("still");//player displays the still texture
			}
			if (spriteChangeCounter == spriteChangeInterval || (currentLobby.accessPlayer(i).playerChar.entityCurrentDirection == 's' && !currentLobby.accessPlayer(i).playerChar.attacking)) {//   player does not change every cycle
				if (!currentLobby.accessPlayer(i).playerChar.attacking) {
					//change player sprite texture
					if (currentDir == 'l') {
						currentLobby.accessPlayer(i).playerChar.changeSpriteTextServer("left");
					}
					else if (currentDir == 'r') {
						currentLobby.accessPlayer(i).playerChar.changeSpriteTextServer("right");
					}
					else if (currentDir == 'u') {
						currentLobby.accessPlayer(i).playerChar.changeSpriteTextServer("up");
					}
					else if (currentDir == 'd') {
						currentLobby.accessPlayer(i).playerChar.changeSpriteTextServer("down");
					}
					//move to the next texture in the array
					currentLobby.accessPlayer(i).playerChar.changeSpriteText("next");
				}
			}


			if (currentLobby.accessPlayer(i).playerChar.attacking) {//if player is attacking
				currentLobby.accessPlayer(i).playerChar.attackTick++;//increment the attack tick
				if (currentLobby.accessPlayer(i).playerChar.attackTick == currentLobby.accessPlayer(i).playerChar.maxAttackTick) {//if player reached the end of the cycle
					currentLobby.accessPlayer(i).playerChar.attacking = false;
					currentLobby.accessPlayer(i).playerChar.attackTick = 0;
					char x = currentLobby.accessPlayer(i).playerChar.entityCurrentDirection;
					currentLobby.accessPlayer(i).playerChar.entityCurrentDirection = 'a';
					//change the player sprite to the direction they are facing
				}
			}
			//if player is damaged
			if (currentLobby.accessPlayer(i).playerChar.damaged) {
				currentLobby.accessPlayer(i).playerChar.damageTick++;
				if (currentLobby.accessPlayer(i).playerChar.damageTick == 61) {
					currentLobby.accessPlayer(i).playerChar.damaged = false;
					currentLobby.accessPlayer(i).playerChar.damageTick = 0;
				}
			}


			newTile = checkMoveTile(currentLobby.accessPlayer(i).playerChar.localPosition, currentLobby.lobbyMaze.getNode(curTile), { static_cast<int>(currentLobby.backgroundRectsArray[0][0][0].getSize().x),static_cast<int>(currentLobby.backgroundRectsArray[0][0][0].getSize().y) });

			if (newTile != curTile) {
				check = { static_cast<int>(newTile.x - curTile.x),static_cast<int>(newTile.y - curTile.y) };
				if (check == vector<int>({ 0, -1 })) {
					currentLobby.accessPlayer(i).playerChar.localPosition = sf::Vector2f(currentLobby.accessPlayer(i).playerChar.localPosition.x, currentLobby.backgroundRectsArray[0][0][0].getSize().y - 50);
				}
				else if (check == vector<int>({ 0, 1 })) {
					currentLobby.accessPlayer(i).playerChar.localPosition = sf::Vector2f(currentLobby.accessPlayer(i).playerChar.localPosition.x, 50);
				}
				else if (check == vector<int>({ -1, 0 })) {
					currentLobby.accessPlayer(i).playerChar.localPosition = sf::Vector2f(currentLobby.backgroundRectsArray[0][0][0].getSize().x - 50, currentLobby.accessPlayer(i).playerChar.localPosition.y);
				}
				else if (check == vector<int>({ 1, 0 })) {
					currentLobby.accessPlayer(i).playerChar.localPosition = sf::Vector2f(50, currentLobby.accessPlayer(i).playerChar.localPosition.y);
				}
				curTile = newTile;

				if (currentLobby.backgroundRectsArray[curTile.x][curTile.y] == vector<sf::RectangleShape>()) {
					currentLobby.backgroundRectsArray[curTile.x][curTile.y] = getCellRectsServer(currentLobby.lobbyMaze.getNode(curTile).pos, currentLobby.lobbyMaze.getNode(curTile).connections);
					currentLobby.collisionRectsArray[curTile.x][curTile.y] = getCollisionRectangles(currentLobby.backgroundRectsArray[curTile.x][curTile.y]);
				}
			}
			for (int j = 0; j < currentLobby.playerCount; j++) {
				if (j != i && currentLobby.accessPlayer(j).playerChar.tile == curTile) {
					currentLobby.accessPlayer(i).sendMessage(currentLobby.accessPlayer(j).playerChar);
				}
			}
		}
		//bot character behavior goes here
			
		//done to here
			
		//enemy behaviour
		for (int i = 0; i < currentLobby.enemyArray.size(); i++) {//iterate through enemy array
			if (currentLobby.enemyArray[i].hpCurrent <= 0) {//if they're dead
				currentLobby.enemyArray.erase(currentLobby.enemyArray.begin() + i);
				break;
			}
			currentLobby.enemyArray[i].tick();
			if (currentLobby.enemyArray[i].directionTick == currentLobby.enemyArray[i].tickMax && !currentLobby.enemyArray[i].attacking) {
				currentLobby.enemyArray[i].behavior(playerCharArray, currentLobby.collisionRectsArray[currentLobby.enemyArray[i].tile.x][currentLobby.enemyArray[i].tile.y]);
				if (currentLobby.enemyArray[i].currentDir == 'l') {
					currentLobby.enemyArray[i].changeSpriteTextServer("left");
				}
				else if (currentLobby.enemyArray[i].currentDir == 'r') {
					currentLobby.enemyArray[i].changeSpriteTextServer("right");
				}
				else if (currentLobby.enemyArray[i].currentDir == 'u') {
					currentLobby.enemyArray[i].changeSpriteTextServer("up");
				}
				else if (currentLobby.enemyArray[i].currentDir == 'd') {
					currentLobby.enemyArray[i].changeSpriteTextServer("down");
				}
			}
			if (!currentLobby.enemyArray[i].attacking) {//if they're not attacking
				currentLobby.enemyArray[i].move(currentLobby.enemyArray[i].currentDir, collObjs);//move
			}
			if (spriteChangeCounter == spriteChangeInterval) {
				if (currentLobby.enemyArray[i].attacking) {
					currentLobby.enemyArray[i].attackTick++;
					if (currentLobby.enemyArray[i].attackTick == currentLobby.enemyArray[i].maxAttackTick) {
						currentLobby.enemyArray[i].attacking = false;
						currentLobby.enemyArray[i].attackTick = 0;
						currentLobby.enemyArray[i].directionTick = currentLobby.enemyArray[i].tickMax - 1;

					}
				}
				//increment texture
				currentLobby.enemyArray[i].changeSpriteTextServer("next");
			}
			if (currentLobby.enemyArray[i].damaged) {
				currentLobby.enemyArray[i].damageTick++;
				if (currentLobby.enemyArray[i].damageTick == 61) {
					currentLobby.enemyArray[i].damaged = false;
					currentLobby.enemyArray[i].damageTick = 0;
				}
			}
			for (int j = 0; j < currentLobby.playerCount; j++) {
				if (currentLobby.accessPlayer(j).playerChar.tile == currentLobby.enemyArray[i].tile) {
					currentLobby.accessPlayer(j).sendMessage(currentLobby.enemyArray[i]);
				}
			}
		}
		for (int j = 0; j < currentLobby.playerCount; j++) {
			currentLobby.accessPlayer(j).sendPreparedMessage();
		}
	}
}

bool updatePreGameLobby(lobby currentLobby){
	return false;
}
