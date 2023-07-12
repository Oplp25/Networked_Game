#pragma once
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>

class item {
public:
	std::string name;
	int cost;
	bool consumable;
	int charges;
	std::string imagePath;

private:
	void useCharge(int charges);
};

