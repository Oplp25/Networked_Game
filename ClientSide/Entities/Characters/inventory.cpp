#include "inventory.h"
#include<iostream>

using namespace std;
inventory::inventory(std::vector<weapon> weaponsp, std::vector<std::pair<item, int>> itemsp)
{
	weapons = weaponsp;
	items = itemsp;
}
