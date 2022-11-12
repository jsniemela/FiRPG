#pragma once
#include "Action.h"
#include "Randomizer.h"
#include "Status.h"

class Character;

class Skill: public Action
{
private:
	int baseDamage;
	int* baseDamagePtr;
	int baseDamageDivider;
	int statusProbability;
	int hpCost;
	int* hpCostPtr;
	int hpCostDivider;
public:

	Skill();
	Skill(std::string newName, DamageType dmgType, bool requiresTarget);
	Skill(std::string newName, int atk, int hp, DamageType dmgType);
	Skill(std::string newName, int atk, int hp, DamageType dmgType, bool req);
	Skill(std::string newName, int* atk, int *hp, int bdd, int hpcd, DamageType dmgType, bool req);
	Skill(std::string newName, int atk, int hp, DamageType dmgType, Effect eff, int statusProb, bool req = true);
	~Skill(){}

	Character* getCharacter();

	void useAction(Character* user, Character* target);
	void useAction(Character* user, std::vector<Character*> targets);
	//void useAction(Character* user);
	int calculateDamage(int damage, bool crit);
	void CreateStatusEffects(Character* target);

	int getHPcost();
protected:
	Character* c;

	//struct attack{};
	
};