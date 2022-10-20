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
	enum damageType { physical, basic, healing, statusOnly, magic, nothing } type;
	Action(std::string newName, damageType newType);
	//Action(std::string newName);
	Action();
	virtual ~Action() {}

	Character* getCharacter();

	std::string getName();
	bool getRequiresTarget();
	damageType getType();
	//void useAction();
	void useAction();
	//void useAction(Character* user);
	//void useAction(Character* user, Character* target);
	//void useAction(Character* user, std::vector<Character*> targets);
};