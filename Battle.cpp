#include "Battle.h"
//comment the next three lines if detecting memory leaks is not necessary
/*
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
*/
Battle::Battle() {}

void Battle::turnOrder(std::vector<std::unique_ptr<Character>>& characters)
{
	//character = &player;
	//character2 = &enemy;
	std::cout << "Turn order: \n";
	//std::cout << characters[0]->getName() << " (speed: " << characters[0]->getSpeed() << ")\n";
	
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
	std::cout << player.getName();
	std::cout << enemy.getName();
	*/
	/*
	for (int i = 0; i < 2; i++)
	{
		std::cout << (characters[i].getName());
	}
	*/
}
/*
void Battle::setupCharacters() {
	std::unique_ptr<Character> hero(new Character{ "Hero", 100, 60, 3, 7, 2, 10, 10 });
	std::unique_ptr<Character> villain(new Character{ "Villain", 100, 60, 3, 7, 2, 10, 10 });
}
*/

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//Character hero { "Hero", 100, 60, 3, 7, 2, 10, 10 };
	//std::unique_ptr<Character> hero(new Character { "Hero", 100, 60, 3, 7, 2, 10, 10 });
	//Character* hero = new Character { "Hero", 100, 60, 3, 7, 2, 10, 10 };
	//std::unique_ptr<Character> villain(new Character { "Villain", 100, 60, 3, 7, 2, 10, 5 });
	//Character villain { "Villain", 100, 10, 3, 7, 2, 10, 5 };
	std::vector<std::unique_ptr<Character>> characters;
	//characters.push_back(hero);
	//characters.push_back(villain);
	characters.push_back(std::unique_ptr<Character> (new Character{ "Hero", 100, 60, 3, 7, 2, 10, 10 }));
	characters.push_back(std::unique_ptr<Character> (new Character{ "Villain", 100, 60, 3, 7, 2, 10, 5 }));

	/*
	for (int i = 0; i < 2; i++)
	{
		characters.push_back(new Character());
	}
	*/
	//Battle battle{characters};
	
	Battle battle;//* battle = new Battle;
	//battle.setupCharacters();
	battle.turnOrder(characters);
	//delete battle;
	
	//battle.turnOrder(hero);
	
	characters[0]->levelUp();
	characters[1]->levelUp();
	characters[0]->showStats();
	std::cout << "\n";
	characters[1]->showStats();
	std::cout << "\n";
	characters[0]->takeTurn();
	characters[0]->dealDamage(*characters[1]);
	characters[0]->showStats();
	characters[1]->showStats();
	//villain.levelUp();
	//villain.showStats();
	
	//delete hero;
	//_CrtDumpMemoryLeaks();
	return 0;
}