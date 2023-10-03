#pragma once
#include "../entity.h"
#include "../Characters/character.h"
#include"enemyTemplates.h"
#include<random>
class enemy :public entity {
	private:
		float aggro = 0.4;//likelyhood of chasing player
		int damage;
		bool isRanged;
		float cooldown;
		int reach;//Melee
		int patrolRange;
		sf::Vector2f baseCoords;//The coords that it patrols around

		bool checkPatRange(char direction);
		std::default_random_engine randGen;
		std::uniform_int_distribution<int> distX;
	public:
		int sight;//How far they can see the player from
		int directionTick;
		int tickMax;

		char currentDir;
		void behavior(character player);
		void tick();
		enemy();
		enemy(enemyTemplate stats, sf::Vector2f startingCoords, sf::Vector2f startingTile);
		enemy(int hpMaxP, float speedP, std::string nameP, float aggroP, int sightP, int damageP, bool isRangedP, float cooldownP, int reachP, int patrolRangeP, std::string imagePathP, sf::Vector2f startingCoords, sf::Vector2f startingTile);
};