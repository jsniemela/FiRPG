#pragma once
#include <iostream>
#include <vector>

class Character;

class Action {
private:
	
protected:
	std::string name;
	bool requiresTarget;
	Character* c;
	
public:
	enum DamageType { physical, basic, healing, statusOnly, magic, none, analyze } type;
	enum Status { nothing, normal, KO, poisoned, sadness, sleep, frozen, burning } effect;
	Action(std::string newName, DamageType newType);
	//Action(std::string newName);
	Action();
	virtual ~Action() {}

	Character* getCharacter();

	std::string getName();
	bool getRequiresTarget();
	DamageType getType();
	void useAction();
	std::string getEffectName();
};