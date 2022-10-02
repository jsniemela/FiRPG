#pragma once
#include "Action.h"
#include "Randomizer.h"

class Character;

class Skill: public Action
{
private:
	int baseDamage;
	bool requiresTarget;
public:
	enum damageType { physical, defensive, healing, statusOnly, fire, ice, nothing } type;
	enum status { normal, poisoned, KO } effect;

	Skill();
	Skill(std::string newName, bool requiresTarget);
	Skill(std::string newName, int atk, damageType dmgType);
	Skill(std::string newName, int atk, damageType dmgType, status eff);
	~Skill(){}

	Character* getCharacter();
	bool getRequiresTarget();

	void useAction(Character* user, Character* target, int atk, int cr);
	void useAction(Character* user);
	float calculateDamage(float damage, bool crit);
	std::string getEffectName();
protected:
	Character* c;

	//struct attack{};
	
};