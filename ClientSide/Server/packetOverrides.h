#pragma once

#include<SFML/Network.hpp>
#include "../Entities/entity.h"

//entity
sf::Packet& operator <<(sf::Packet& packet, const entity& toSend);
sf::Packet& operator >>(sf::Packet& packet, entity& toSend);