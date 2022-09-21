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
public:
	Battle();
	void turnOrder(std::vector<Character*>& characters);
	void simulateBattle();
	std::vector<Character*> setupCharacters();
	//void turnOrder(Character &player);
	//void turnOrder();
};