#include "CharacterManager.h"

CharacterManager::CharacterManager(int money)
	: money{money}
{

}

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
		ch->recoverSP(ch->getMaxSP());
		ch->showStats();
	}
}

std::vector<Character*> CharacterManager::getCharacters()
{
	return characters;
}

int CharacterManager::getMoney()
{
	return money;
}

void CharacterManager::receiveMoney(int gainedMoney)
{
	money += gainedMoney;
	std::cout << "Gained " << gainedMoney << " money. Total: " << money << ".\n\n";
}