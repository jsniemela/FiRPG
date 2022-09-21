#pragma once
#include "Character.h"
#include <iostream>
#include <vector>

class Battle
{
private:
	//Character* character;
	//Character* character2;
	std::vector<Character*> players;
	std::vector<Character*> enemies;
	std::vector<Character*> characters;
public:
	Battle();
	void turnOrder();
	void simulateBattle();
	void setupCharacters();
	//void turnOrder(Character &player);
	//void turnOrder();
};