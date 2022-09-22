#include "Battle.h"
#include "CharacterManager.h"
#include <algorithm>
//comment the next three lines if detecting memory leaks is not necessary
/*
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
*/

Battle::Battle(std::vector<Character*> enms, std::vector<Character*> plrs) 
	: enemies{enms}, players{plrs}
{

}

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
	characters.insert(characters.end(), players.begin(), players.end());
	characters.insert(characters.end(), enemies.begin(), enemies.end());

	return characters;
}

void Battle::simulateBattle()
{
	std::vector<Character*> characters = setupCharacters();
	turnOrder(characters);
	players[0]->setTarget(enemies[0]);
	players[1]->setTarget(enemies[0]);
	enemies[0]->setTarget(players[0]);
	enemies[1]->setTarget(players[0]);

	while (players[0]->getStatus() != Character::KO && enemies[0]->getStatus() != Character::KO) // TODO: check if all characters from one side are dead
	{
		for (auto character : characters)
		{
			character->showStats();
			character->takeTurn();
			// TODO: check deaths here too, change target to next with +1 and break loop if not targets left.
		}
	}
	std::cout << "Exiting battle.\n";

	for (auto c : characters)
	{
		delete c;
	}
	characters.clear();
}


int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Character* p1 = new Character("Player1", 100, 10, 3, 7, 2, 25, 10);
	Character* p2 = new Character("Player2", 100, 10, 3, 7, 2, 25, 8);
	Character* e1 = new Character("Enemy1", 100, 10, 3, 7, 2, 25, 12);
	Character* e2 = new Character("Enemy2", 100, 10, 3, 7, 2, 25, 6);

	CharacterManager cm;
	cm.addPlayers(p1);
	cm.addPlayers(p2);
	cm.addEnemies(e1);
	cm.addEnemies(e2);
	
	Battle battle(cm.getEnemies(), cm.getPlayers());

	battle.simulateBattle();
	//_CrtDumpMemoryLeaks();
	return 0;
}