#pragma once
#include<SFML/Graphics.hpp>

class entity {

	private:
		sf::Vector2f actualPos;//actual position on the map
	public:
		int hp;
		int maxHp;
		sf::Vector2f tilePos;//Position on the tile that it it on
		sf::Vector2f tile;//Position of the tile that it is on
		entity();
		void move();
		void damage();
		void death();
		void spawn();
		void meleeAttack();


};