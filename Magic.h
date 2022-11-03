#pragma once
#include "Action.h"

class Character;
class Magic : public Action
{
private:
	int baseDamage;
	int spCost;
	//bool targetAll;
public:
	enum Element { fire, ice, healing, none } element;

	Magic();
	Magic(std::string newName, int dmg, int sp, DamageType dmgType, Element elem, bool req, Status eff = nothing);
	~Magic() {}

	Character* getCharacter();

	void useAction(Character* user, Character* target);
	void useAction(Character* user, std::vector<Character*> targets);

	int getSPcost();
protected:
	Character* c;
};