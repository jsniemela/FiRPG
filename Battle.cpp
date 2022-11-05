#include "Battle.h"
#include <algorithm>
#include <chrono>
#include <thread>

Battle::Battle(std::vector<Character*> enms, std::vector<Character*> plrs) 
	: enemies{enms}, players{plrs}
{
	expTotal = 0;
}

Battle::~Battle()
{
	std::cout << "Battle ended\n\n";
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
				if (en->getCurrentHealth() < 1)
				{
					deadEnemies++;
				}
			}

			if (deadPlayers == players.size() || deadEnemies == enemies.size())
			{
				for (auto en : enemies) 
				{
					expTotal += en->getExpDrop();
				}
				for (auto pl : players)
				{
					if (pl->getCurrentHealth() > 0)
					{
						pl->gainExp(expTotal);
					}
				}
				break;
			}
		}
	}
	std::cout << "Exiting battle. \n\n";
	for (auto pl : players)
	{
		pl->showStats();
	}
	
	/*
	for (auto c : characters)
	{
		delete c;
	}
	characters.clear();
	*/
}
