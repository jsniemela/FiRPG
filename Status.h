#pragma once
#include <iostream>

class Status
{
private:

public:
	std::string name;
	int duration;
	int damagePerTurn; // damage that the character takes every turn, negative values for healing(?)
	int skipProbability; // percentage probability of chacter skipping a turn because of the status. 0 for no skip
	int dmgMultiplier; // positive values means character takes more damage and negative means less
	Status(std::string n, int dur, int dmg, int skip, int dmgMult);
};