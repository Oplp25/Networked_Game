#include<random>
#include<vector>
#include<iostream>
#include<filesystem>
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
	mazeGraph layout = createArenaLayout();
	sf::Vector2f starter = sf::Vector2f(500, 500);
	sf::Vector2f origin = sf::Vector2f(0, 0);
	enemy x = enemy(orcSwordsman, starter, origin);
	vector<enemy> enemyArrayP = {x};//Will be created by createArenaLayout, but for now will just be manually added
	
	//vector<enemy> enemyArrayP = {};
	vector<character> charsArrayP = {};//list of the AI controlled characters
	string result = singleArenaGameloop(win,playerCharacter, charsArrayP, enemyArrayP,layout);//run the gameloop
	if (result == "exit") {
		return void();
	}
	else if (result == "win") {
		spWin(win);
	}
	else if (result == "loss") {
		spLoss(win);
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
	vector<sf::RectangleShape> backgroundRects = getCellRects(currentMazeGraph.getNode(player.tile).pos, currentMazeGraph.getNode(player.tile).connections,win);

	vector<vector<sf::Vector2f*>> collObjs;//collision objects. 

	for (int i = 0; i < enemyArray.size();i++) {
		collObjs.push_back({&enemyArray[i].tile, &enemyArray[i].localPosition });//add enemy coords
	}for (int i = 0; i < charsArray.size(); i++) {
		collObjs.push_back({ &charsArray[i].tile, &charsArray[i].localPosition });//add bot coords
	}
	collObjs.push_back({ &player.tile, &player.localPosition });//add player coords

	//Temporary tile boundaries. tile =1840,1000

	/*sf::RectangleShape topBoundary(sf::Vector2f(1920, 40));
	topBoundary.setPosition(sf::Vector2f(0, 0));
	topBoundary.setFillColor(colours::cinereous);
	sf::RectangleShape bottomBoundary(sf::Vector2f(1920, 40));
	bottomBoundary.setPosition(sf::Vector2f(0, 1040));
	bottomBoundary.setFillColor(colours::cinereous);
	sf::RectangleShape rightBoundary(sf::Vector2f(40, 1080));
	rightBoundary.setPosition(sf::Vector2f(1880, 0));
	rightBoundary.setFillColor(colours::cinereous);
	sf::RectangleShape leftBoundary(sf::Vector2f(40, 1080));
	leftBoundary.setPosition(sf::Vector2f(0, 0));
	leftBoundary.setFillColor(colours::cinereous);*/

	/*sf::RectangleShape temp2 = sf::RectangleShape(sf::Vector2f(64, 64));
	temp2.setOutlineColor(sf::Color(0, 0, 255));
	temp2.setOutlineThickness(5);
	temp2.setFillColor(sf::Color::Transparent);

	sf::RectangleShape temp3 = sf::RectangleShape(sf::Vector2f(64, 64));
	temp3.setOutlineColor(sf::Color(0, 0, 255));
	temp3.setOutlineThickness(5);
	temp3.setFillColor(sf::Color::Transparent);
	
	sf::CircleShape temp4(enemyArray[0].sight);
	temp4.setOutlineColor(sf::Color(255, 0, 0));
	temp4.setOutlineThickness(5);
	temp4.setFillColor(sf::Color::Transparent);
	
	sf::CircleShape temp5(enemyArray[0].reach);
	temp5.setOutlineColor(sf::Color(255, 0, 0));
	temp5.setOutlineThickness(5);
	temp5.setFillColor(sf::Color::Transparent);

	sf::CircleShape temp6(player.currentWeapon.reach);
	temp6.setOutlineColor(sf::Color(255, 0, 0));
	temp6.setOutlineThickness(5);
	temp6.setFillColor(sf::Color::Transparent);

	sf::RectangleShape temp7 = sf::RectangleShape(sf::Vector2f(player.currentWeapon.sprite.getLocalBounds().width, player.currentWeapon.sprite.getLocalBounds().height));
	temp7.setOutlineColor(sf::Color(0, 0, 255));
	temp7.setOutlineThickness(5);
	temp7.setFillColor(sf::Color::Transparent);*/


	while (!finished) {
		//player graphics
		if (player.hpCurrent <= 0) {//if player is dead
			return "loss";
		}
		currentDir = playerBehavior(win, player,enemyArray, collObjs);//get the direction of motion for the player
		if (currentDir == 'e') {
			return "exit";
		}
		if (currentDir == 's' && !player.attacking) {
			player.changeSpriteText("still");//player displays the still texture
		}
		if (spriteChangeCounter == spriteChangeInterval || ( player.entityCurrentDirection == 's' && !player.attacking)) {//   player does not change every cycle
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
				if (enemyArray.empty()) {
					return "win";//if no enemies left
				}
				break;
			}
			if (enemyArray[i].tile == player.tile) {// only update texture if they on the same tile as the player
				enemyArray[i].tick();
				if (enemyArray[i].directionTick == enemyArray[i].tickMax && !enemyArray[i].attacking) {
					enemyArray[i].behavior(player);
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
					if (enemyArray[i].attacking) {
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
				if (enemyArray[i].damaged) {
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

		//to reflect a sprite, do sprite.setScale(-1,1)
		win.draw(player.draw());
		win.draw(player.currentWeapon.draw());
		/*temp2.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y);
		temp2.setOrigin(player.sprite.getOrigin());
		temp2.setScale(player.sprite.getScale());
		temp2.setRotation(player.sprite.getRotation());
		temp6.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y);
		temp6.setOrigin(player.sprite.getOrigin());
		temp6.setScale(player.sprite.getScale());
		temp6.setRotation(player.sprite.getRotation());
		temp7.setPosition(player.currentWeapon.sprite.getPosition().x, player.currentWeapon.sprite.getPosition().y);
		temp7.setOrigin(player.currentWeapon.sprite.getOrigin());
		temp7.setScale(player.currentWeapon.sprite.getScale());
		temp7.setRotation(player.currentWeapon.sprite.getRotation());
		temp7.setSize(sf::Vector2f(player.currentWeapon.sprite.getLocalBounds().width, player.currentWeapon.sprite.getLocalBounds().height));
		win.draw(temp6);
		win.draw(temp7);
		win.draw(temp2);*/
		for (character i : charsArray) {//draw bots
			win.draw(i.draw());
			win.draw(i.currentWeapon.draw());
		}
		for (enemy i : enemyArray) {
			if (i.tile == player.tile) {
				win.draw(i.draw());//only draw if on same tile as player
				/*temp3.setPosition(i.sprite.getPosition().x, i.sprite.getPosition().y);
				temp3.setOrigin(i.sprite.getOrigin());
				temp3.setScale(i.sprite.getScale());
				temp3.setRotation(i.sprite.getRotation());
				/*temp4.setPosition(i.sprite.getPosition().x, i.sprite.getPosition().y);
				temp4.setOrigin(temp4.getGlobalBounds().width/2, temp4.getGlobalBounds().height / 2);
				temp4.setScale(i.sprite.getScale());
				temp4.setRotation(i.sprite.getRotation());
				temp5.setPosition(i.sprite.getPosition().x, i.sprite.getPosition().y);
				temp5.setOrigin(temp5.getGlobalBounds().width / 2, temp5.getGlobalBounds().height / 2);
				temp5.setScale(i.sprite.getScale());
				temp5.setRotation(i.sprite.getRotation());
				win.draw(temp5);
				win.draw(temp3);
				win.draw(temp4);*/
			}
				
		}
		win.display();
		spriteChangeCounter++;
		if (spriteChangeCounter > spriteChangeInterval) {
			spriteChangeCounter = 0;
		}
		//frames++;
	}
	return string();
}

string multiArenaGameloop(sf::RenderWindow& win, character& player, vector<vector<vector<sf::Texture>>> textures)
{
	return string();
}