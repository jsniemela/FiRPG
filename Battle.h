#pragma once
#include "Character.h"
#include <iostream>
#include <vector>

class Battle
{
private:
	//Character* character;
	//Character* character2;
public:
	Battle();
	void turnOrder(std::vector<Character*>& characters);
	void simulateBattle();
	//void setupCharacters();
	//void turnOrder(Character &player);
	//void turnOrder();
};