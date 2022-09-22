#include "CharacterManager.h"

void CharacterManager::addPlayers(Character* plr)
{
	players.push_back(plr);
}

void CharacterManager::addEnemies(Character* enm)
{
	enemies.push_back(enm);
}

std::vector<Character*> CharacterManager::getPlayers()
{
	return players;
}

std::vector<Character*> CharacterManager::getEnemies()
{
	return enemies;
}