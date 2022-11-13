#pragma once
#include <iostream>
#include <vector>

class Character;
class Status;

class Action {
private:
	
protected:
	std::string name;
	bool requiresTarget;
	Character* c;
	Status* s;
	
public:
	enum DamageType { physical, basic, healing, statusOnly, magic, none, analyze } type;
	enum Effect { nothing, normal, KO, poisoned, sadness, sleep, frozen, burning, protect, shell } effect;
	Action(std::string newName, DamageType newType);
	//Action(std::string newName);
	Action();
	virtual ~Action() {}

	Character* getCharacter();
	Status* getStatus();

	std::string getName();
	bool getRequiresTarget();
	DamageType getType();
	void useAction();
	std::string getEffectName();

	void CreateStatusEffects(Character* target);
};