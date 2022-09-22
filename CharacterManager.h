#pragma once
#include <vector>
#include "Character.h"

class CharacterManager
{
private:
	std::vector<Character*> characters;
public:
	void addCharacters(Character* ch);
	std::vector<Character*> getCharacters();
};