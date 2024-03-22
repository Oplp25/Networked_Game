#pragma once
#include<SFML/Graphics.hpp>
#include "../GraphicsFunctions/drawable/drawable.h"

//base class for things that move aroud the maze and have multiple animations
class entity:public drawable {

	protected:
		//a method to switch which is the current texture array
		void switchTextArray(char direction, char d2 = ' ', char d3 = ' ');//direction is the direction, or a if attacking. d2 is left or right when attacking, d3 is the direction you are attacking in(only for the player)
		//array of text arrays
		std::vector<std::vector<sf::Texture>> listOfTexts = { {},{},{},{},{},{},{} };// up, down,right, still, rightAttack, upRightAttack,downRightAttack	
		float speed;

		bool checkEnd(char direction, int nums, std::vector<std::vector<int>> tileLayout);//Checks whether a character is going to move off the edge of the map. returns true if the move is OK
	public:
		char entityCurrentDirection = 's';
		bool damaged = false;//are they in the damage animation - they cannot be damaged if true
		int damageTick = 0;
		int hpMax;
		int hpCurrent;
		int attackTick = 0;//current tick
		int maxAttackTick = 3;//how many cycles it takes to do the attack animation
		bool attacking = false;//are they attacking
		std::string name;
		void changeSpriteText(std::string textArgs);//change the texture of the sprite
		void loadTextures();//load all the textures from file
		entity();//empty constructor
		void attack(entity &ent, int damage);//method to attack
		void move(char direction, std::vector<std::vector<sf::Vector2f*>> collObjs, std::vector<std::vector<int>> tileLayout );//move the entity
		void damageSelf(int damage);//take damage
		void death();
		void spawn();
		int getCurrentText() const;


};