#include "serverMain.h"

#include<SFML/Network.hpp>
#include<iostream>
#include<thread>

#include "lobby.h"
#include "../GraphicsFunctions/Maze/mazeFuncs.h"
#include "../Behavior/Player/playerBehavior.h"
using namespace std;

int runServer() {

	cout << "Booted" << endl;
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

	}
	/*
	sf::TcpSocket clientSocket;
	listener.accept(clientSocket);
	std::cout << "New client connected: " << clientSocket.getRemoteAddress() << std::endl;

	char buffer[1024];
	std::size_t received = 0;
	clientSocket.receive(buffer, sizeof(buffer), received);
	std::cout << "The client said: " << buffer << std::endl;

	clientSocket.send("Hello World",15);

	sf::Packet packet;
	clientSocket.receive(packet);
	string x;
	packet >> x;
	std::cout << "The client said: " << x << std::endl;
	cin >> x;
	*/
	return 0;
}


void tickGame(lobby currentLobby) {
	bool finished = false;
	vector<int> check;
	vector<sf::RectangleShape> backgroundRects = getCellRects(currentLobby.lobbyMaze.getNode(currentLobby.accessPlayer(i).playerChar.tile).pos, currentLobby.lobbyMaze.getNode(currentLobby.accessPlayer(i).playerChar.tile).connections, win);

	vector<vector<int>> collisionRectangles = getCollisionRectangles(backgroundRects);
	vector<vector<sf::Vector2f*>> collObjs;//collision objects. 

	for (int i = 0; i < currentLobby.enemyArray.size(); i++) {
		collObjs.push_back({ &currentLobby.enemyArray[i].tile, &currentLobby.enemyArray[i].localPosition });//add enemy coords
	}
	//Bot list
	/*for (int i = 0; i < charsArray.size(); i++) {
		collObjs.push_back({ &charsArray[i].tile, &charsArray[i].localPosition });//add bot coords
		}*/
	for (int i = 0; i < currentLobby.playerCount; i++) {
		collObjs.push_back({ &currentLobby.accessPlayer(i).playerChar.tile, &currentLobby.accessPlayer(i).playerChar.localPosition});//add player coords
	}


	while (!finished) {
		//player graphics
		for (int i = 0; i < currentLobby.playerCount; i++) {
			if (currentLobby.accessPlayer(i).playerChar.hpCurrent <= 0) {//if player is dead
				currentLobby.accessPlayer(i).addToMessage("dead");
			}
			//need to use sockets to get inputs
			//currentLobby.accessPlayer(i).currentDir = playerBehavior(win, player, currentLobby.enemyArray, collObjs, collisionRectangles);//get the direction of motion for the player

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
					currentLobby.accessPlayer(i).playerChar.sprite.setColor(sf::Color(255, 255, 255));//make them flash red
				}
			}

			//Done up to here

			sf::Event event;
			while (win.pollEvent(event)) {
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {// if x in corner of window clicked or escape pressed
					win.close();
					return "exit";//exit the game
				}
			}

			newTile = checkMoveTile(currentLobby.accessPlayer(i).playerChar.localPosition, currentLobby.lobbyMaze.getNode(currentLobby.accessPlayer(i).playerChar.tile), { static_cast<int>(backgroundRects[0].getSize().x),static_cast<int>(backgroundRects[0].getSize().y) });

			if (newTile != currentLobby.accessPlayer(i).playerChar.tile) {
				check = { static_cast<int>(newTile.x - currentLobby.accessPlayer(i).playerChar.tile.x),static_cast<int>(newTile.y - currentLobby.accessPlayer(i).playerChar.tile.y) };
				if (check == vector<int>({ 0, -1 })) {
					currentLobby.accessPlayer(i).playerChar.localPosition = sf::Vector2f(currentLobby.accessPlayer(i).playerChar.localPosition.x, backgroundRects[0].getSize().y - 50);
				}
				else if (check == vector<int>({ 0, 1 })) {
					currentLobby.accessPlayer(i).playerChar.localPosition = sf::Vector2f(currentLobby.accessPlayer(i).playerChar.localPosition.x, 50);
				}
				else if (check == vector<int>({ -1, 0 })) {
					currentLobby.accessPlayer(i).playerChar.localPosition = sf::Vector2f(backgroundRects[0].getSize().x - 50, currentLobby.accessPlayer(i).playerChar.localPosition.y);
				}
				else if (check == vector<int>({ 1, 0 })) {
					currentLobby.accessPlayer(i).playerChar.localPosition = sf::Vector2f(50, currentLobby.accessPlayer(i).playerChar.localPosition.y);
				}
				currentLobby.accessPlayer(i).playerChar.tile = newTile;
				backgroundRects = getCellRects(currentLobby.lobbyMaze.getNode(currentLobby.accessPlayer(i).playerChar.tile).pos, currentLobby.lobbyMaze.getNode(currentLobby.accessPlayer(i).playerChar.tile).connections, win);
				collisionRectangles = getCollisionRectangles(backgroundRects);
			}
			//bot character behavior. very outdated
			for (character i : charsArray) {
				//currentDir = characterBehavior(i);
				if (currentDir == 's') {
					i.changeSpriteText("still");
				}
				else if (spriteChangeCounter == spriteChangeInterval) {
					if (!i.attacking) {
						if (currentDir == 'l') {
							i.changeSpriteText("left");
						}
						else if (currentDir == 'r') {
							i.changeSpriteText("right");
						}
						else if (currentDir == 'u') {
							i.changeSpriteText("up");
						}
						else if (currentDir == 'd') {
							i.changeSpriteText("down");
						}
						i.changeSpriteText("next");
					}
					else {
						i.changeSpriteText("next");
					}
				}
				i.sprite.setPosition(i.localPosition);
				i.currentWeapon.sprite.setPosition(i.localPosition);
			}

			//enemy graphics

			for (int i = 0; i < currentLobby.enemyArray.size(); i++) {//iterate through enemy array
				if (currentLobby.enemyArray[i].hpCurrent <= 0) {//if they're dead
					currentLobby.enemyArray.erase(currentLobby.enemyArray.begin() + i);
					if (currentLobby.enemyArray.empty()) {
						return "win";//if no enemies left
					}
					break;
				}
				if (currentLobby.enemyArray[i].tile == currentLobby.accessPlayer(i).playerChar.tile) {// only update texture if they on the same tile as the player
					currentLobby.enemyArray[i].tick();
					if (currentLobby.enemyArray[i].directionTick == currentLobby.enemyArray[i].tickMax && !currentLobby.enemyArray[i].attacking) {
						currentLobby.enemyArray[i].behavior(player, collisionRectangles);
						if (currentLobby.enemyArray[i].currentDir == 'l') {
							currentLobby.enemyArray[i].changeSpriteText("left");
						}
						else if (currentLobby.enemyArray[i].currentDir == 'r') {
							currentLobby.enemyArray[i].changeSpriteText("right");
						}
						else if (currentLobby.enemyArray[i].currentDir == 'u') {
							currentLobby.enemyArray[i].changeSpriteText("up");
						}
						else if (currentLobby.enemyArray[i].currentDir == 'd') {
							currentLobby.enemyArray[i].changeSpriteText("down");
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
						currentLobby.enemyArray[i].changeSpriteText("next");
					}
					if (currentLobby.enemyArray[i].damaged) {
						currentLobby.enemyArray[i].damageTick++;
						if (currentLobby.enemyArray[i].damageTick == 61) {
							currentLobby.enemyArray[i].damaged = false;
							currentLobby.enemyArray[i].damageTick = 0;
							currentLobby.enemyArray[i].sprite.setColor(sf::Color(255, 255, 255));
						}
					}
				}
			}
		}
}

bool updatePreGameLobby(lobby currentLobby){
	return false;
}
