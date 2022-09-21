#include "Battle.h"
#include <algorithm>
//comment the next three lines if detecting memory leaks is not necessary

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

Battle::Battle() {
}

void Battle::turnOrder()
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

void Battle::setupCharacters() 
{
	
	characters.push_back(new Character { "Player1", 100, 10, 3, 7, 2, 25, 10 });
	characters.push_back(new Character { "Player2", 100, 10, 3, 7, 2, 25, 10 });
	characters.push_back(new Character{ "Enemy", 100, 10, 3, 7, 2, 25, 5 });
	characters.push_back(new Character{ "Enemy2", 100, 10, 3, 7, 2, 25, 5 });
	/*
	characters.resize(players.size() + enemies.size());
	characters.insert(characters.end(), players.begin(), players.end());
	characters.insert(characters.end(), enemies.begin(), enemies.end());
	*/
}

void Battle::simulateBattle()
{
	setupCharacters();
	turnOrder();

	players[0]->levelUp();
	enemies[0]->levelUp();
	players[0]->showStats();
	std::cout << "\n";
	enemies[0]->showStats();
	std::cout << "\n";
	//for (int i = 0; i < 3; i++)
	players[0]->setTarget(enemies[0]);
	enemies[0]->setTarget(players[0]);

	while (players[0]->getStatus() != Character::KO && enemies[0]->getStatus() != Character::KO)
	{
		for (auto character : characters)
		{
			character->showStats();
			character->takeTurn();
		}
	}
	std::cout << "Exiting battle.\n";
	/*
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
			std::cout << "A character has died.\n";
			break;
		}
	}
	std::cout << "Exiting battle.\n";
	*/
	for (auto p : characters)
	{
		delete p;
	}
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