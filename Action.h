#pragma once
#include <iostream>
#include <vector>
//#include "Character.h"

class Action {
private:
	
protected:
	std::string name;
public:
	Action(std::string newName);
	//Action(std::string newName);
	Action(){}
	virtual ~Action() {}

	std::string getName();
	void useAction();
};