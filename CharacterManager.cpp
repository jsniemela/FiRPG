#include "CharacterManager.h"

void CharacterManager::addCharacters(Character* ch)
{
	characters.push_back(ch);
}

std::vector<Character*> CharacterManager::getCharacters()
{
	return characters;
}
