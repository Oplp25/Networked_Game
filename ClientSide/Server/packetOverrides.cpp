#include "packetOverrides.h"

//insertion
sf::Packet& operator<<(sf::Packet& packet, const entity& toSend)
{
    sf::Uint8 currentText = toSend.getCurrentText();

    return packet << toSend.localPosition.x << toSend.localPosition.y << currentText;
    // TODO: insert return statement here
}

//extraction
sf::Packet& operator>>(sf::Packet& packet, entity& toSend)
{
    // TODO: insert return statement here
}
