#include "enemy.h"
#include <math.h>

using namespace std;

bool enemy::checkPatRange(char direction)
{
	if (direction == 'u' && (sqrt(pow((localPosition.y - speed - baseCoords.y),2)+pow(localPosition.x-baseCoords.x,2)) < patrolRange)) {
		return true;
	}
	if (direction == 'd' && (sqrt(pow((localPosition.y + speed - baseCoords.y), 2) + pow(localPosition.x - baseCoords.x, 2)) < patrolRange)) {
		return true;
	}
	if (direction == 'r' && (sqrt(pow((localPosition.y - baseCoords.y), 2) + pow(localPosition.x + speed - baseCoords.x, 2)) < patrolRange)) {
		return true;
	}
	if (direction == 'l' && (sqrt(pow((localPosition.y - baseCoords.y), 2) + pow(localPosition.x - speed - baseCoords.x, 2)) < patrolRange)) {
		return true;
	}
	return false;
}

void enemy::behavior(character player)
{
	if (false and std::sqrt((pow((player.localPosition.x-localPosition.x),2)+pow((player.localPosition.y - localPosition.y),2)))<sight) {
		//if player in range and not attacking:
		//	Attack player
		//else:
		//	Move towards player
		//return dir
	}
	else {
		bool x = true;
		randGen.seed(time(0));
		vector<char> dirs = {'u','d','l','r'};
		char dir;
		while (x) {
			dir = dirs[distX(randGen)];
			if (checkEnd(dir) && checkPatRange(dir) && dir+currentDir!=217 && dir+currentDir != 222) {
				x = false;
			}
		}
		/*int choice = distX(randGen);
		cout << "choice"<<choice << endl;
		dir = dirs[choice];*/
		currentDir = dir;
	}
}

enemy::enemy()
{
	damage = 0;
	cooldown = 0;
	reach = 0;
	name = "";
	imagePath = "";
	aggro = 0;
	sight = 0;
	isRanged = 0;
	patrolRange = 0;
	speed = 0;
	hpMax = 1;
	directionTick = 0;
}

enemy::enemy(enemyTemplate stats, sf::Vector2f startingCoords, sf::Vector2f startingTile)
{
	damage = stats.damage;
	cooldown = stats.cooldown;
	reach = stats.reach;
	name = stats.name;
	imagePath = stats.imagePath;
	aggro = stats.aggro;
	sight = stats.sight;
	isRanged = stats.isRanged;
	patrolRange = stats.patrolRange;
	baseCoords = startingCoords;
	tile = startingTile;
	localPosition = startingCoords;
	hpCurrent = stats.hpMax;
	hpMax = stats.hpMax;
	speed = stats.speed;
	loadTextures();
	distX = uniform_int_distribution<int>(0, 3);
	directionTick = 0;
	tickMax = 25;
}

enemy::enemy(int hpMaxP, float speedP, std::string nameP, float aggroP, int sightP, int damageP, bool isRangedP, float cooldownP, int reachP, int patrolRangeP, std::string imagePathP, sf::Vector2f startingCoords, sf::Vector2f startingTile)
{
	damage = damageP;
	cooldown = cooldownP;
	reach = reachP;
	name = nameP;
	imagePath = imagePathP;
	aggro = aggroP;
	sight = sightP;
	isRanged = isRangedP;
	patrolRange = patrolRangeP;
	speed = speedP;
	hpMax = hpMaxP;
	baseCoords = startingCoords;
	tile = startingTile;
	localPosition = startingCoords;
	loadTextures();
	distX = uniform_int_distribution<int>(0, 3);
	directionTick = 0;
}

void enemy::tick() {
	directionTick++;
	if (directionTick > tickMax+1){
		directionTick = 0;
	}
	move(currentDir);
}
