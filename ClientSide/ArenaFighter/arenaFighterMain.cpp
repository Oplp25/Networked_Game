#include<random>
#include<vector>
#include<iostream>
#include<filesystem>
#include<fstream>
#include "arenaFighterMain.h"
#include "../CharacterCreator/characterCreator.h"
#include "../GraphicsFunctions/Colours/colourConsts.h"
#include "../Behavior/Player/playerBehavior.h"
#include "../Entities/Enemies/enemyTemplates.h"
#include "../GraphicsFunctions/gameOutcomes.h"
#include "../GraphicsFunctions/Maze/mazeFuncs.h"
//#include "../GraphicsFunctions/textureLoaders/textureLoaders.h"
using namespace std;
const filesystem::path cwd = filesystem::current_path();
mazeGraph createArenaLayout()
{
	mazeGraph graph = genGraph();
	//populate with enemies and loot
	return graph;
}

void runArenaFighterSingle(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);//create the player character
	//character player2 = playerCharacter;
	//player2.localPosition = sf::Vector2f(750,500);
	mazeGraph layout = createArenaLayout();//create layout from function
	sf::Vector2f starter = sf::Vector2f(win.getSize().x/3+32, win.getSize().y/ 3 + 32);//coordinate to place the test enemy at
	sf::Vector2f origin = sf::Vector2f(0, 0);
	enemy x = enemy(orcSwordsman, starter, origin);
	vector<enemy> enemyArrayP = {x};//Will be created by createArenaLayout, but for now will just be manually added
	
	//vector<enemy> enemyArrayP = {};
	vector<character> charsArrayP = {};//list of the AI controlled characters
	string result = singleArenaGameloop(win,playerCharacter, charsArrayP, enemyArrayP,layout);//run the gameloop
	if (result == "exit") {//If the user terminstes the program
		return void();//close
	}
	else if (result == "win") {//if the player wins
		spWin(win);//run win screen
	}
	else if (result == "loss") {//if the player loses
		spLoss(win);//run loss screen
		}
}

void runArenaFighterMulti(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);
}

string singleArenaGameloop(sf::RenderWindow& win, character& player, vector<character> charsArray,vector<enemy> enemyArray, mazeGraph currentMazeGraph)
{
	//seting up variables
	bool won = false;
	bool finished = false;
	int spriteChangeCounter = 0;
	int spriteChangeInterval = 12;
	char currentDir = 's';
	vector<int> check;

	//Background Rects are to draw on the screen, dynamically generated based on tile.
	vector<sf::RectangleShape> backgroundRects = getCellRects(currentMazeGraph.getNode(player.tile).pos, currentMazeGraph.getNode(player.tile).connections,win);

	vector<vector<int>> collisionRectangles = getCollisionRectangles(backgroundRects);//BackgroundRecs but for collision
	vector<vector<sf::Vector2f*>> collObjs;//collision objects. 

	for (int i = 0; i < enemyArray.size();i++) {
		collObjs.push_back({&enemyArray[i].tile, &enemyArray[i].localPosition });//add enemy coords
	}for (int i = 0; i < charsArray.size(); i++) {
		collObjs.push_back({ &charsArray[i].tile, &charsArray[i].localPosition });//add bot coords
	}
	collObjs.push_back({ &player.tile, &player.localPosition });//add player coords
	
	sf::Vector2f newTile = player.tile;

	//testing variable for if the background is just green
	sf::RectangleShape fullGreenBackground(sf::Vector2f(win.getSize().x, win.getSize().y));
	fullGreenBackground.setFillColor(colours::hunterGreen);
	fullGreenBackground.setPosition(sf::Vector2f(0, 0));

	sf::Clock clock;
	while (!finished) {
		//player graphics
		if (player.hpCurrent <= 0) {//if player is dead
			sf::Time elapsed = clock.getElapsedTime();
			return "loss";
		}
		currentDir = playerBehavior(win, player, enemyArray, collObjs, collisionRectangles);//get the direction of motion for the player
		if (currentDir == 'e') {
			return "exit";
		}
		if (currentDir == 's' && !player.attacking) {
			player.changeSpriteText("still");//player displays the still texture
		}
		if (spriteChangeCounter == spriteChangeInterval || (player.entityCurrentDirection == 's' && !player.attacking)) {//   player does not change every cycle
			if (!player.attacking) {
				//change player sprite texture
				if (currentDir == 'l') {
					player.changeSpriteText("left");
				}
				else if (currentDir == 'r') {
					player.changeSpriteText("right");
				}
				else if (currentDir == 'u') {
					player.changeSpriteText("up");
				}
				else if (currentDir == 'd') {
					player.changeSpriteText("down");
				}
				//move to the next texture in the array
				player.changeSpriteText("next");
			}
			else {//if player is attacking
				player.changeSpriteText("next");//move to the next texture in the array
				player.attackTick++;//increment the attack tick
				if (player.attackTick == player.maxAttackTick) {//if player reached the end of the cycle
					player.attacking = false;
					player.attackTick = 0;
					char x = player.entityCurrentDirection;
					player.entityCurrentDirection = 'a';
					//change the player sprite to the direction they are facing
					if (x == 'l') {
						player.changeSpriteText("left");
					}
					else if (x == 'r') {
						player.changeSpriteText("right");
					}
					else if (x == 'u') {
						player.changeSpriteText("up");
					}
					else if (x == 'd') {
						player.changeSpriteText("down");
					}
					else if (x == 's') {
						player.changeSpriteText("still");
					}

				}
			}
		}
		//if player is damaged
		if (player.damaged) {
			player.damageTick++;
			if (player.damageTick == 61) {
				player.damaged = false;
				player.damageTick = 0;
				player.sprite.setColor(sf::Color(255, 255, 255));//make them flash red
			}
		}

		sf::Event event;
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {// if x in corner of window clicked or escape pressed
				win.close();
				return "exit";//exit the game
			}
		}

		//checks if the player should move tile
		newTile = checkMoveTile(player.localPosition, currentMazeGraph.getNode(player.tile), {static_cast<int>(backgroundRects[0].getSize().x),static_cast<int>(backgroundRects[0].getSize().y)});

		if (newTile != player.tile) {//if the tile is changing
			//changes newTile to relative coords
			check = { static_cast<int>(newTile.x - player.tile.x),static_cast<int>(newTile.y - player.tile.y) };

			//when the player changes tile, this changes their position to the opposite side, so it appears like they moved.
			if (check == vector<int>({ 0, -1 })) {
				player.localPosition = sf::Vector2f(player.localPosition.x, backgroundRects[0].getSize().y - 50);//50 instead of 49 so they are not caught in an endless loop of changing tile
			}
			else if (check == vector<int>({ 0, 1 })) {
				player.localPosition = sf::Vector2f(player.localPosition.x, 50);
			}
			else if (check == vector<int>({ -1, 0 })) {
				player.localPosition = sf::Vector2f(backgroundRects[0].getSize().x - 50, player.localPosition.y);
			}
			else if (check == vector<int>({1, 0})) {
				player.localPosition = sf::Vector2f(50, player.localPosition.y);
			}
			player.tile = newTile;
			//update backgroundRects and collisionRectangles for the new tile
			backgroundRects = getCellRects(currentMazeGraph.getNode(player.tile).pos, currentMazeGraph.getNode(player.tile).connections, win);
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
		
		for (int i = 0; i < enemyArray.size();i++) {//iterate through enemy array
			if (enemyArray[i].hpCurrent <= 0) {//if they're dead
				enemyArray.erase(enemyArray.begin()+i);
				if (enemyArray.empty()) {//if no enemies left
					sf::Time elapsed = clock.getElapsedTime();
					ofstream f;
					f.open("HighScores.txt", ios::app);
					f << elapsed.asSeconds() << endl;
					f.close();
					return "win";
				}
				break;
			}
			if (enemyArray[i].tile == player.tile) {// only update texture if they on the same tile as the player
				enemyArray[i].tick();
				if (enemyArray[i].directionTick == enemyArray[i].tickMax && !enemyArray[i].attacking) {//if the enemy needs to change direction
					enemyArray[i].behavior(player, collisionRectangles);//enemy behaviour algorithm
					//update textures
					if (enemyArray[i].currentDir == 'l') {
						enemyArray[i].changeSpriteText("left");
					}
					else if (enemyArray[i].currentDir == 'r') {
						enemyArray[i].changeSpriteText("right");
					}
					else if (enemyArray[i].currentDir == 'u') {
						enemyArray[i].changeSpriteText("up");
					}
					else if (enemyArray[i].currentDir == 'd') {
						enemyArray[i].changeSpriteText("down");
					}
				}
				if (!enemyArray[i].attacking) {//if they're not attacking
					enemyArray[i].move(enemyArray[i].currentDir,collObjs);//move
				}
				if (spriteChangeCounter == spriteChangeInterval) {
					if (enemyArray[i].attacking) {//if they are attacking
						enemyArray[i].attackTick++;
						if (enemyArray[i].attackTick == enemyArray[i].maxAttackTick) {
							enemyArray[i].attacking = false;
							enemyArray[i].attackTick = 0;
							enemyArray[i].directionTick = enemyArray[i].tickMax - 1;

						}
					}
					//increment texture
					enemyArray[i].changeSpriteText("next");
				}
				if (enemyArray[i].damaged) {//if they are damaged
					enemyArray[i].damageTick++;
					if (enemyArray[i].damageTick == 61) {
						enemyArray[i].damaged = false;
						enemyArray[i].damageTick = 0;
						enemyArray[i].sprite.setColor(sf::Color(255, 255, 255));
					}
				}
			}
		}

		//drawing graphics
		win.clear(colours::hunterGreen);
		//Draw background
		for (sf::RectangleShape i : backgroundRects) {
			win.draw(i);
		}
		//win.draw(fullGreenBackground);
		//to reflect a sprite, do sprite.setScale(-1,1)
		win.draw(player.draw());
		win.draw(player.currentWeapon.draw());

		for (character i : charsArray) {//draw bots
			win.draw(i.draw());
			win.draw(i.currentWeapon.draw());
		}
		for (enemy i : enemyArray) {
			if (i.tile == player.tile) {
				win.draw(i.draw());//only draw if on same tile as player
			}
				
		}
		win.display();
		//increment sprite change counter
		spriteChangeCounter++;
		if (spriteChangeCounter > spriteChangeInterval) {
			spriteChangeCounter = 0;
		}
	}
	return string();
}

string multiArenaGameloop(sf::RenderWindow& win, character& player, vector<vector<vector<sf::Texture>>> textures)
{
	return string();
}