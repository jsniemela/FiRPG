#include "CharacterManager.h"

void CharacterManager::addCharacters(Character* ch)
{
	characters.push_back(ch);
}

void CharacterManager::clearCharacters()
{
	characters.clear();
}

void CharacterManager::healCharacters()
{
	for (auto ch : characters)
	{
		ch->recoverStatus();
		ch->recover(ch->getMaxHealth());
	}
}

std::vector<Character*> CharacterManager::getCharacters()
{
	return characters;
}
