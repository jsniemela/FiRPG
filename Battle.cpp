#include "Battle.h"
#include "CharacterManager.h"
#include <algorithm>
#include <chrono>
#include <thread>
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

	while (deadPlayers != players.size() && deadEnemies != enemies.size()) 
	{
		for (auto character : characters)
		{
			deadPlayers = 0;
			deadEnemies = 0;
			if (character->getStatus() != Character::KO)
			{
				character->takeTurn();
				std::chrono::seconds dura(1);
				std::this_thread::sleep_for(dura);
			}

			for (auto pl : players)
			{
				if (pl->getStatus() == Character::KO) 
				{
					deadPlayers++;
				}
			}

			for (auto en : enemies) 
			{
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
	std::cout << "Exiting battle. \n\n";
	for (auto ch : characters)
	{
		ch->showStats();
	}
	
	for (auto c : characters)
	{
		delete c;
	}
	characters.clear();
	
}

void createCharacters(CharacterManager& pm, CharacterManager& em)
{
	pm.addCharacters(new Character("Player 1", 100, 20, 15, 3, 7, 2, 19, 10, true));
	pm.addCharacters(new Character("Player 2", 100, 20, 13, 3, 7, 2, 18, 8, true));
	pm.addCharacters(new Character("Player 3", 100, 20, 13, 3, 7, 2, 20, 8, true));
	em.addCharacters(new Character("Enemy 1", 100, 20, 12, 3, 7, 2, 21, 12, false));
	em.addCharacters(new Character("Enemy 2", 100, 20, 12, 5, 7, 2, 18, 6, false));
	em.addCharacters(new Character("Enemy 3", 100, 20, 12, 5, 7, 2, 17, 6, false));
}

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CharacterManager pm; //player manager
	CharacterManager em; //enemy manager
	createCharacters(pm, em);

	Battle battle(em.getCharacters(), pm.getCharacters());
	battle.simulateBattle();
	//_CrtDumpMemoryLeaks();
	return 0;
}