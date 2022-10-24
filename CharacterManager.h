#pragma once
#include <vector>
#include "Character.h"

class CharacterManager
{
private:
	std::vector<Character*> characters;
	int money;
public:
	void addCharacters(Character* ch);
	void clearCharacters();
	void healCharacters();
	void receiveMoney(int gainedMoney);

	std::vector<Character*> getCharacters();
	int getMoney();

	CharacterManager(int money);
};