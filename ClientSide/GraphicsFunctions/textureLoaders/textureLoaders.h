#pragma once
#include<vector>
#include<filesystem>
#include<SFML/Graphics.hpp>
#include "../../Entities/Characters/character.h"

std::vector<std::vector<std::vector<sf::Texture>>> loadOtherCharacterTextures(std::vector<character> characterList);

std::vector<std::vector<std::vector<sf::Texture>>> loadTextures(character myChar);

std::vector<std::vector<sf::Texture>> characterTextureLoader(character aCharacter);//Left, Right, Up, Down, Misc

std::vector<std::vector<sf::Texture>> weaponTextureLoader();//sword, axe, hammer, bow, arrow