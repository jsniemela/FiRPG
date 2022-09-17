#include "Battle.h"
#include <algorithm>
//comment the next three lines if detecting memory leaks is not necessary
/*
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
*/
Battle::Battle() {}

void Battle::turnOrder(std::vector<std::unique_ptr<Character>>& characters)
{
	std::cout << "Turn order: \n";
	//this currently sorts the list for all contexts, consider making a local vector
	std::sort(characters.begin(), characters.end(), 
		[](const std::unique_ptr<Character> &left, const std::unique_ptr<Character> &right)
		{
			return left->getSpeed() > right->getSpeed();
		});
	for (int i = 0; i < characters.size(); i++)
	{
		std::cout << characters[i]->getName() << "\n";
	}
	std::cout << std::endl;
}

std::vector<std::unique_ptr<Character>> setupCharacters() {
	std::vector<std::unique_ptr<Character>> characters;
	characters.push_back(std::unique_ptr<Character>(new Character{ "Hero", 100, 10, 3, 7, 2, 25, 10 }));
	characters.push_back(std::unique_ptr<Character>(new Character{ "Villain", 100, 10, 3, 7, 2, 25, 15 }));
	return characters;
}


int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::vector<std::unique_ptr<Character>> characters = setupCharacters();
	
	Battle battle;
	battle.turnOrder(characters);
	
	characters[0]->levelUp();
	characters[1]->levelUp();
	characters[0]->showStats();
	std::cout << "\n";
	characters[1]->showStats();
	std::cout << "\n";
	//for (int i = 0; i < 3; i++)
	while(characters[0]->getStatus() != Character::KO || characters[0]->getStatus() != Character::KO)
	{
		int i = 0;
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
		i++;
		if (i > 100) { //temporary solution in case loop doesn't end with someone dying.
			std::cout << "100 rounds passed without anyone dying. Breaking loop"; 
			break;
		}
	}

	//villain.levelUp();
	//villain.showStats();
	
	//_CrtDumpMemoryLeaks();
	return 0;
}