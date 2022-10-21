#pragma once
#include <vector>
#include "Character.h"

class CharacterManager
{
private:
	std::vector<Character*> characters;
public:
	void addCharacters(Character* ch);
	void clearCharacters();
	std::vector<Character*> getCharacters();
};