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

std::vector<Character*> Battle::setupCharacters()
{
	std::vector<Character*> characters;
	
	Character* p1 = new Character("Player1", 100, 10, 3, 7, 2, 25, 10);
	Character* p2 = new Character("Player2", 100, 10, 3, 7, 2, 25, 8);
	Character* e1 = new Character("Enemy1", 100, 10, 3, 7, 2, 25, 12);
	Character* e2 = new Character("Enemy2", 100, 10, 3, 7, 2, 25, 6);
	
	players.push_back(p1);
	players.push_back(p2);
	enemies.push_back(e1);
	enemies.push_back(e2);

	characters.insert(characters.end(), players.begin(), players.end());
	characters.insert(characters.end(), enemies.begin(), enemies.end());
	
	return characters;
}

void Battle::simulateBattle()
{
	std::vector<Character*> characters = setupCharacters();
	turnOrder(characters);
	/*
	players[0]->levelUp();
	enemies[0]->levelUp();
	players[0]->showStats();
	std::cout << "\n";
	enemies[0]->showStats();
	std::cout << "\n";
	//for (int i = 0; i < 3; i++)
	*/
	players[0]->setTarget(enemies[0]);
	players[1]->setTarget(enemies[0]);
	enemies[0]->setTarget(players[0]);
	enemies[1]->setTarget(players[0]);

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
	for (auto c : characters)
	{
		delete c;
	}
	characters.clear();
	/*
	for (auto p : players)
	{
		delete p;
	}
	players.clear();
	for (auto e : enemies)
	{
		delete e;
	}
	enemies.clear();
	*/
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Battle battle;
	battle.simulateBattle();

	_CrtDumpMemoryLeaks();
	return 0;
}