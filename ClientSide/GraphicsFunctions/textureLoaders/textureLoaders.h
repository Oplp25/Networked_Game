#pragma once
#include<vector>
#include<filesystem>
#include<SFML/Graphics.hpp>
#include "../../Entities/Characters/character.h"

std::vector<std::string> iWeapons = { "sword" };


std::vector<std::vector<std::vector<sf::Texture>>> loadOtherCharacterTextures(std::vector<character> characterList);//Loads other Character's textures that aren't the player's

std::vector<std::vector<std::vector<sf::Texture>>> loadTextures(character myChar);// Loads the Player, Weapon, Terrain and Item Textures

std::vector<std::vector<std::vector<sf::Texture>>> loadEnemyTextures();//Loads the textures for the enemies

std::vector<std::vector<sf::Texture>> characterTextureLoader(character aCharacter);//Left, Right, Up, Down, Misc

std::vector<std::vector<sf::Texture>> weaponTextureLoader();//sword, axe, hammer, bow, arrow; hilt/no hilt