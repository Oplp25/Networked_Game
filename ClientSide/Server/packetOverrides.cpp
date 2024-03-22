#include "packetOverrides.h"

//insertion
sf::Packet& operator<<(sf::Packet& packet, const entity& toSend)
{
    sf::Uint8 currentText = toSend.getCurrentText();
    return packet << toSend.localPosition.x << toSend.localPosition.y << currentText << toSend.tile.x << toSend.tile.y << toSend.entityCurrentDirection << toSend.damaged << toSend.attacking;
}

//extraction
sf::Packet& operator>>(sf::Packet& packet, entity& toSend)
{
    return packet >> toSend.localPosition.x >> toSend.localPosition.y >> toSend.currentText >> toSend.tile.x >> toSend.tile.y >> toSend.entityCurrentDirection >> toSend.damaged >> toSend.attacking;
}
