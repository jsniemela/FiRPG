#pragma once
#include "Action.h"

class Character;
class Magic : public Action
{
private:
	int baseDamage;
	//bool targetAll;
public:
	enum Element { fire, ice, healing } element;

	Magic();
	Magic(std::string newName, int dmg, damageType dmgType, Element elem, bool req);
	~Magic() {}

	Character* getCharacter();

	void useAction(Character* user, Character* target);
	void useAction(Character* user, std::vector<Character*> targets);
protected:
	Character* c;
};