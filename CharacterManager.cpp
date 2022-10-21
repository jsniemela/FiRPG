#include "CharacterManager.h"

void CharacterManager::addCharacters(Character* ch)
{
	characters.push_back(ch);
}

void CharacterManager::clearCharacters()
{
	characters.clear();
}

std::vector<Character*> CharacterManager::getCharacters()
{
	return characters;
}
