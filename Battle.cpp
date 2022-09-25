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

	int deadPlayers = 0;
	int deadEnemies = 0;

	for (auto pl : players) {
		pl->setEnemyList(enemies);
		pl->setPlayerList(players);
	}
	for (auto en : enemies) {
		en->setEnemyList(players);
		en->setPlayerList(enemies);
	}

	while (deadPlayers != players.size() && deadEnemies != enemies.size()) //unnecessary? no. the break inside for loop would only break the for loop
	{
		for (auto character : characters)
		{
			deadPlayers = 0;
			deadEnemies = 0;
			if (character->getStatus() != Character::KO)
			{
				character->takeTurn();
			}

			for (auto pl : players) {
				if (pl->getStatus() == Character::KO) 
				{
					deadPlayers++;
				}
			}

			for (auto en : enemies) {
				if (en->getStatus() == Character::KO)
				{
					deadEnemies++;
				}
			}

			if (deadPlayers == players.size() || deadEnemies == enemies.size())
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
	Character* p3 = new Character("Player3", 100, 13, 3, 7, 2, 25, 8);
	Character* e1 = new Character("Enemy1", 100, 12, 3, 7, 2, 25, 12);
	Character* e2 = new Character("Enemy2", 100, 12, 5, 7, 2, 25, 6);
	Character* e3 = new Character("Enemy3", 100, 12, 5, 7, 2, 25, 6);

	CharacterManager pm; //player manager
	CharacterManager em; //enemy manager
	pm.addCharacters(p1);
	pm.addCharacters(p2);
	pm.addCharacters(p3);
	em.addCharacters(e1);
	em.addCharacters(e2);
	em.addCharacters(e3);
	
	Battle battle(em.getCharacters(), pm.getCharacters());

	battle.simulateBattle();
	//_CrtDumpMemoryLeaks();
	return 0;
}