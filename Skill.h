#pragma once
#include "Action.h"
#include "Randomizer.h"

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
	enum status { normal, poisoned, KO, sadness, sleep } effect;

	Skill();
	Skill(std::string newName, damageType dmgType, bool requiresTarget);
	Skill(std::string newName, int atk, int hp, damageType dmgType);
	Skill(std::string newName, int atk, int hp, damageType dmgType, bool req);
	Skill(std::string newName, int* atk, int *hp, int bdd, int hpcd, damageType dmgType, bool req);
	Skill(std::string newName, int atk, int hp, damageType dmgType, status eff, int statusProb);
	Skill(std::string newName, int atk, int hp, damageType dmgType, status eff, int statusProb, bool req);
	~Skill(){}

	Character* getCharacter();

	void useAction(Character* user, Character* target);
	void useAction(Character* user, std::vector<Character*> targets);
	//void useAction(Character* user);
	float calculateDamage(float damage, bool crit);
	std::string getEffectName();

	int getHPcost();
protected:
	Character* c;

	//struct attack{};
	
};