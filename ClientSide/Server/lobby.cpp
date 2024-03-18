#include "lobby.h"

player& lobby::accessPlayer(int playerNumber)
{
	return playerList[playerNumber];
}
