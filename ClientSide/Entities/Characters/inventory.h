#pragma once
#include<vector>
#include "../../Items/item.h"
#include "../../Items/Weapons/weapon.h"

class inventory {
	public:
		inventory(std::vector <weapon> weaponsp = {}, std::vector<std::pair<item, int>> itemsp = {});
		//When adding new vectors, use vector<class> classes for objects that you can only have one of, and vector<pair<class,int>> classes for objects that you can have multiple of
		std::vector <weapon> weapons;//A vector of all of the weapons held
		std::vector<std::pair<item, int>> items;
};