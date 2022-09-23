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

std::vector<Character*> Battle::turnOrder()
{
	std::vector<Character*> characters;
	characters.insert(characters.end(), players.begin(), players.end());
	characters.insert(characters.end(), enemies.begin(), enemies.end());

	std::sort(characters.begin(), characters.end(), 
		[](Character* &left, Character* &right)
		{
			return left->getSpeed() > right->getSpeed();
		});

	return characters;
}

void Battle::simulateBattle()
{
	std::vector<Character*> characters = turnOrder();
	for (auto pl : players) {
		pl->setEnemyList(enemies);
		pl->setPlayerList(players);
	}
	for (auto en : enemies) {
		en->setEnemyList(players);
		en->setPlayerList(enemies);
	}

	while (players.back()->getStatus() != Character::KO && enemies.back()->getStatus() != Character::KO) //unnecessary?
	{
		for (auto character : characters)
		{
			character->takeTurn();
			if (players.back()->getStatus() == Character::KO || enemies.back()->getStatus() == Character::KO) //extra check so that remaining players don't take their turn
			{
				break;
			}
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

	Character* p1 = new Character("Player1", 100, 15, 3, 7, 2, 25, 10);
	Character* p2 = new Character("Player2", 100, 13, 3, 7, 2, 25, 8);
	Character* e1 = new Character("Enemy1", 100, 8, 3, 7, 2, 25, 12);
	Character* e2 = new Character("Enemy2", 100, 10, 3, 7, 2, 25, 6);

	CharacterManager pm; //player manager
	CharacterManager em; //enemy manager
	pm.addCharacters(p1);
	pm.addCharacters(p2);
	em.addCharacters(e1);
	em.addCharacters(e2);
	
	Battle battle(em.getCharacters(), pm.getCharacters());

	battle.simulateBattle();
	//_CrtDumpMemoryLeaks();
	return 0;
}