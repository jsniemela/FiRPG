#pragma once
#include <iostream>

class Action {
private:
	
protected:
	std::string name;
public:
	Action(std::string newName);
	Action(){}
	virtual ~Action() {}

	std::string getName();
};