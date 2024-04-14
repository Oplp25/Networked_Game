#pragma once
#include "../entity.h"
#include"enemyTemplates.h"
#include<random>
class enemy :public entity {
	private:
		float aggro = 0.4;//likelyhood of chasing player
		int damage;//amount of damge it does per hit
		bool isRanged;//is it ranged
		float cooldown;//the attack cooldown
		int patrolRange;//the distance it can go from baseCoords
		sf::Vector2f baseCoords;//The coords that it patrols around cock

		bool checkPatRange(char direction);//check if a move will go outside of the patrol range
		std::default_random_engine randGen;// the random engine to generate random numbers
		std::uniform_int_distribution<int> distX;//a uniform distrobution:every number has an equal chance of being chosen
	public:
		int reach;//Melee
		int sight;//How far they can see the player from
		int directionTick;//current tick
		int tickMax;//how many cycles it walks in one dicertion for

		char currentDir;// current direction
		void behavior(std::vector<entity&> playerArray, std::vector<std::vector<int>> tileLayout);//method to determine what it will do
		void tick();//increment the tick
		void move(char direction, std::vector<std::vector<sf::Vector2f*>> collObjs);
		enemy();//empty constructor
		enemy(enemyTemplate stats, sf::Vector2f startingCoords, sf::Vector2f startingTile);//template constructor
		//variable constructor
		enemy(int hpMaxP, float speedP, std::string nameP, float aggroP, int sightP, int damageP, bool isRangedP, float cooldownP, int reachP, int patrolRangeP, std::string imagePathP, sf::Vector2f startingCoords, sf::Vector2f startingTile);
};