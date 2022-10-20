#include "Field.h"
#include "CharacterManager.h"

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