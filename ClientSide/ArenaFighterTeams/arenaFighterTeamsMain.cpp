#include "arenaFighterTeamsMain.h"
#include "../CharacterCreator/characterCreator.h"

void runArenaFighterTeamsSingle(sf::RenderWindow& win, sf::TcpSocket& socket)
{
	character playerCharacter = characterCreator(win);
}

void runArenaFighterTeamsMulti(sf::RenderWindow& win, sf::TcpSocket& socket)
{
	character playerCharacter = characterCreator(win);
}

void createArenaLevel(int currentLevel)
{
}

void singleArenaGameloop()
{
}

void multiArenaGameloop()
{
}
