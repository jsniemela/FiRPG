#pragma once
#include <vector>
#include "Character.h"

class CharacterManager
{
private:
	std::vector<Character*> players;
	std::vector<Character*> enemies;
public:
	void addPlayers(Character* plr);
	void addEnemies(Character* enm);
	std::vector<Character*> getPlayers();
	std::vector<Character*> getEnemies();
};