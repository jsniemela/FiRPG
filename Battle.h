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
	void turnOrder(std::vector<std::unique_ptr<Character>>& characters);
	//void setupCharacters();
	//void turnOrder(Character &player);
	//void turnOrder();
};