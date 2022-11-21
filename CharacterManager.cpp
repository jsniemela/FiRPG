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
	for (auto ch : characters)
	{
		delete(ch);
	}
	characters.clear();
}

bool CharacterManager::partyAlive() // returns true if at least one character is alive
{
	for (auto ch : characters)
	{
		if (ch->getCurrentHealth() > 0)
			return true;
	}
	return false;
}

void CharacterManager::healCharacters()
{
	for (auto ch : characters)
	{
		if (ch->getStatus() == Character::KO)
		{
			ch->revive();
		}
		ch->clearStatuses();
		if (ch->getCurrentHealth() < ch->getMaxHealth())
		{
			ch->recover(ch->getMaxHealth());
		}
		else
		{
			std::cout << ch->getName() << " is already at full health.\n";
		}
		if (ch->getCurrentSP() < ch->getMaxSP())
		{
			ch->recoverSP(ch->getMaxSP());
		}
		else
		{
			std::cout << ch->getName() << " is already at full SP.\n";
		}
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

CharacterManager::~CharacterManager()
{
	//clearCharacters();
}