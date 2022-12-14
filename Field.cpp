#include "Field.h"
#include "CharacterManager.h"

//comment the next three lines if detecting memory leaks is not necessary
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void createPlayers(CharacterManager& pm)
{
	pm.addCharacters(new Character("Player 1", 100, 20, 15, 3, 7, 2, 19, 10, true));
	pm.addCharacters(new Character("Player 2", 100, 20, 13, 3, 7, 2, 18, 8, true));
	pm.addCharacters(new Character("Player 3", 100, 20, 13, 3, 7, 2, 20, 8, true));
}

void createEnemies(CharacterManager& em)
{
	em.addCharacters(new Character("Enemy 1", 200, 5, 6, 3, 7, 2, 21, 12, false, Character::Weakness::fire));
	em.addCharacters(new Character("Enemy 2", 200, 5, 6, 5, 7, 2, 18, 6, false, Character::Weakness::fire));
	em.addCharacters(new Character("Enemy 3", 200, 5, 6, 5, 7, 2, 17, 6, false, Character::Weakness::fire));
}

void CreateBattle(CharacterManager pm, CharacterManager em)
{
	Battle battle(em.getCharacters(), pm.getCharacters());
	battle.simulateBattle();
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		CharacterManager pm(0); //player manager
		CharacterManager em(50); //enemy manager
		createPlayers(pm);
		int choice = 1;
	
		while (choice > 0 && choice < 4)
		{
			std::cout << "(1)Start Battle\n(2)Heal\n(3)Equip weapons (test)\n(4)Exit\nMake your choice: ";
			std::cin >> choice;
			switch (choice)
			{
				case 1:
					if (pm.partyAlive()) 
					{
						std::cout << "Starting a new battle.\n\n";
							createEnemies(em);
							CreateBattle(pm, em);
							if (pm.partyAlive())
								pm.receiveMoney(em.getMoney());
							em.clearCharacters();
					}
					else
					{
						std::cout << "Can't start a battle with everyone dead\n";
					}
					break;
				case 2:
					std::cout << "Healed everyone!\n\n";
					pm.healCharacters();
					break;
				case 3: 
					for (auto pl : pm.getCharacters())
					{
						pl->EquipWeapon(new Weapon(Weapon::sword, 5, "Wooden sword"));
					}
				default:
					break;
			}
		
		}
		pm.clearCharacters();
		em.clearCharacters();
	}
	std::cout << "Exiting...";
	_CrtDumpMemoryLeaks();
	return 0;
}