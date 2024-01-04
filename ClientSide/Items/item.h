#pragma once
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include "../GraphicsFunctions/drawable/drawable.h"
// a base class for things that can be picked up like weapons
class item: public drawable {
public:
	std::string name;
	int cost;
	bool consumable;
	int charges;

private:
	void useCharge(int charges);
};

