#include "Battle.h"
#include <algorithm>
//comment the next three lines if detecting memory leaks is not necessary

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

Battle::Battle() {}

void Battle::turnOrder(std::vector<std::unique_ptr<Character>>& characters)
{
	//character = &player;
	//character2 = &enemy;
	std::cout << "Turn order: \n";
	//std::cout << characters[0]->getName() << " (speed: " << characters[0]->getSpeed() << ")\n";
	
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters[i]->getStatus() == Character::haste)
		{
			//never mind, do this in Character
		}
	}
	
	if (characters[0]->getSpeed() > characters[1]->getSpeed())
	{
		std::cout << characters[0]->getName() << " (speed: " << characters[0]->getSpeed() << ")\n";
		std::cout << characters[1]->getName() << " (speed: " << characters[1]->getSpeed() << ")\n\n";
	}
	else
	{
		std::cout << characters[1]->getName() << " (speed: " << characters[1]->getSpeed() << ")\n";
		std::cout << characters[0]->getName() << " (speed: " << characters[0]->getSpeed() << ")\n\n";
	}

	/*
	std::sort(characters.begin(), characters.end(), 
		[](Character &left, Character& right)
		{
			return left.getSpeed() < right.getSpeed();
		});
	*/
	/*
	for (int i = 0; i < characters.size(); i++)
	{
		std::cout << characters[i]->getName() << " (speed: " << characters[0]->getSpeed() << ")\n";
	}
	std::cout << "\n";
	*/
}

std::vector<std::unique_ptr<Character>> setupCharacters() {
	std::vector<std::unique_ptr<Character>> characters;
	characters.push_back(std::unique_ptr<Character>(new Character{ "Hero", 100, 60, 3, 7, 2, 10, 10 }));
	characters.push_back(std::unique_ptr<Character>(new Character{ "Villain", 100, 60, 3, 7, 2, 10, 5 }));
	return characters;
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::vector<std::unique_ptr<Character>> characters = setupCharacters();
	
	Battle battle;
	battle.turnOrder(characters);
	
	characters[0]->levelUp();
	characters[1]->levelUp();
	characters[0]->showStats();
	std::cout << "\n";
	characters[1]->showStats();
	std::cout << "\n";
	for (int i = 0; i < 3; i++)
	{
		if (characters[0]->getStatus() != Character::KO && characters[1]->getStatus() != Character::KO)
		{
			characters[0]->takeTurn();
			characters[0]->dealDamage(*characters[1]);
			characters[1]->showStats();
		}
		if (characters[1]->getStatus() != Character::KO && characters[1]->getStatus() != Character::KO)
		{
			characters[1]->takeTurn();
			characters[1]->dealDamage(*characters[0]);
			characters[0]->showStats();
		}
	}

	//villain.levelUp();
	//villain.showStats();
	
	//delete hero;
	_CrtDumpMemoryLeaks();
	return 0;
}