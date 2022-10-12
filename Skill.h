#pragma once
#include "Action.h"
#include "Randomizer.h"

class Character;

class Skill: public Action
{
private:
	int baseDamage;
	int statusProbability;
public:
	enum status { normal, poisoned, KO, sadness, sleep } effect;

	Skill();
	Skill(std::string newName, damageType dmgType, bool requiresTarget);
	Skill(std::string newName, int atk, damageType dmgType);
	Skill(std::string newName, int atk, damageType dmgType, status eff, int statusProb);
	~Skill(){}

	Character* getCharacter();

	void useAction(Character* user, Character* target);
	void useAction(Character* user);
	float calculateDamage(float damage, bool crit);
	std::string getEffectName();
protected:
	Character* c;

	//struct attack{};
	
};