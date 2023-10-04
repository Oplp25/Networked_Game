#include<random>
#include<vector>
#include<filesystem>
#include "arenaFighterMain.h"
#include "../CharacterCreator/characterCreator.h"
#include "../GraphicsFunctions/Colours/colourConsts.h"
#include "../Behavior/Player/playerBehavior.h"
#include "../Entities/Enemies/enemyTemplates.h"
//#include "../GraphicsFunctions/textureLoaders/textureLoaders.h"
using namespace std;
const filesystem::path cwd = filesystem::current_path();
void createArenaLayout()
{
}

void runArenaFighterSingle(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);
	character player2 = playerCharacter;
	player2.localPosition = sf::Vector2f(750,500);
	//layout = createArenaLayout()
	sf::Vector2f starter = sf::Vector2f(500, 500);
	sf::Vector2f origin = sf::Vector2f(0, 0);
	enemy x = enemy(orcSwordsman, starter, origin);
	vector<enemy> enemyArrayP = {x};//Will be created by createArenaLayout, but for now will just be manually added
	vector<character> charsArrayP = {};//list of the AI controlled characters
	string result = singleArenaGameloop(win,playerCharacter, charsArrayP, enemyArrayP);
	if (result == "exit") {
		return void();
	}
}

void runArenaFighterMulti(sf::RenderWindow& win)
{
	character playerCharacter = characterCreator(win);
}

string singleArenaGameloop(sf::RenderWindow& win, character& player, vector<character> charsArray,vector<enemy> enemyArray)
{
	//seting up variables
	bool won = false;
	bool finished = false;
	int spriteChangeCounter = 0;
	int spriteChangeInterval = 12;
	char currentDir = 's';

	//Temporary tile boundaries. tile =1840,1000
	sf::RectangleShape topBoundary(sf::Vector2f(1920,40));
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
	leftBoundary.setFillColor(colours::cinereous);

	sf::RectangleShape temp2 = sf::RectangleShape(sf::Vector2f(64, 64));
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

	while (!finished) {
		//player graphics
		currentDir = playerBehavior(win, player);
		if (currentDir == 'e') {
			return "exit";
		}
		if (currentDir == 's') {
			player.changeSpriteText("still");
		}
		if (spriteChangeCounter == spriteChangeInterval){
			if (!player.attacking) {
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
				player.changeSpriteText("next");
			}
			else {
				player.changeSpriteText("next");
			}
		}

		sf::Event event;
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				win.close();
				return "exit";
			}
		}

		//AI character behavior
		for (character i : charsArray) {
			//currentDir = characterBehavior(i);
			if (currentDir == 's') {
				i.changeSpriteText("still");
			}
			if (spriteChangeCounter == spriteChangeInterval) {
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
		
		for (int i = 0; i < enemyArray.size();i++) {
			if (enemyArray[i].tile == player.tile) {
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
				if (!enemyArray[i].attacking) {
					enemyArray[i].move(enemyArray[i].currentDir);
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
					enemyArray[i].changeSpriteText("next");
				}
			}
		}

		//drawing graphics
		win.clear(colours::hunterGreen);
		//Draw background
		win.draw(topBoundary);
		win.draw(bottomBoundary);
		win.draw(bottomBoundary);
		win.draw(rightBoundary);
		win.draw(leftBoundary);

		//to reflect a sprite, do sprite.setScale(-1,1)
		win.draw(player.draw());
		temp2.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y);
		temp2.setOrigin(player.sprite.getOrigin());
		temp2.setScale(player.sprite.getScale());
		temp2.setRotation(player.sprite.getRotation());
		//win.draw(temp2);
		//win.draw(player.currentWeapon.draw());
		for (character i : charsArray) {
			win.draw(i.draw());
			win.draw(i.currentWeapon.draw());
		}
		for (enemy i : enemyArray) {
			if (i.tile == player.tile) {
				win.draw(i.draw());
				cout << i.localPosition.x << " " << i.localPosition.y<<endl;
				temp3.setPosition(i.sprite.getPosition().x, i.sprite.getPosition().y);
				temp3.setOrigin(i.sprite.getOrigin());
				temp3.setScale(i.sprite.getScale());
				temp3.setRotation(i.sprite.getRotation());
				temp4.setPosition(i.sprite.getPosition().x, i.sprite.getPosition().y);
				temp4.setOrigin(temp4.getGlobalBounds().width/2, temp4.getGlobalBounds().height / 2);
				temp4.setScale(i.sprite.getScale());
				temp4.setRotation(i.sprite.getRotation());
				temp5.setPosition(i.sprite.getPosition().x, i.sprite.getPosition().y);
				temp5.setOrigin(temp5.getGlobalBounds().width / 2, temp5.getGlobalBounds().height / 2);
				temp5.setScale(i.sprite.getScale());
				temp5.setRotation(i.sprite.getRotation());
				/*win.draw(temp4);
				win.draw(temp3);
				win.draw(temp5);*/
			}
				
		}
		win.display();
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