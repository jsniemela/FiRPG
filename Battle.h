#pragma once
#include "Character.h"
//#include <iostream>
//#include <vector>

class Battle
{
private:
	std::vector<Character*> enemies; 
	std::vector<Character*> players;
	//Character* character;
	//Character* character2;
public:
	Battle(std::vector<Character*> enms, std::vector<Character*> plrs);
	std::vector<Character*> turnOrder();
	void simulateBattle();
	//void turnOrder(Character &player);
	//void turnOrder();
};