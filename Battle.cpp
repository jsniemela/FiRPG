#include "Battle.h"
#include <algorithm>
//comment the next three lines if detecting memory leaks is not necessary

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

Battle::Battle() {}

void Battle::turnOrder(std::vector<Character*>& characters)
{
	std::cout << "Turn order: \n";
	//this currently sorts the list for all contexts, consider making a local vector
	std::sort(characters.begin(), characters.end(), 
		[](Character* &left, Character* &right)
		{
			return left->getSpeed() > right->getSpeed();
		});
	for (int i = 0; i < characters.size(); i++)
	{
		std::cout << characters[i]->getName() << "\n";
	}
	std::cout << std::endl;
}

std::vector<Character*> setupCharacters() {
	std::vector<Character*> characters;
	characters.push_back(new Character { "Hero", 100, 10, 3, 7, 2, 25, 10 });
	characters.push_back(new Character{ "Villain", 100, 10, 3, 7, 2, 25, 15 });
	return characters;
}

void Battle::simulateBattle()
{
	std::vector<Character*> characters = setupCharacters();
	turnOrder(characters);

	characters[0]->levelUp();
	characters[1]->levelUp();
	characters[0]->showStats();
	std::cout << "\n";
	characters[1]->showStats();
	std::cout << "\n";
	//for (int i = 0; i < 3; i++)
	characters[0]->setTarget(characters[1]);
	characters[1]->setTarget(characters[0]);
	for (int i = 0; i < 100; i++)
	{
		std::cout << "turn: " << i << std::endl;
		if (characters[0]->getStatus() != Character::KO && characters[1]->getStatus() != Character::KO)
		{
			characters[0]->takeTurn();
			characters[1]->showStats();
		}
		else {
			std::cout << "A character died.\n";
			break;
		}
		if (characters[1]->getStatus() != Character::KO && characters[1]->getStatus() != Character::KO)
		{
			characters[1]->takeTurn();
			characters[0]->showStats();
		}
		else {
			std::cout << "A character died.\n";
			break;
		}
	}
	std::cout << "Exiting battle.\n";
	characters.clear();
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Battle battle;
	battle.simulateBattle();

	_CrtDumpMemoryLeaks();
	return 0;
}