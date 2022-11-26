#pragma once
#include <iostream>

struct Status
{
	std::string name;
	const int duration; // default duration for the status effect
	int turnsLeft; // turns left with the status effect
	int damagePerTurn; // damage that the character takes every turn, negative values for healing(?)
	int skipProbability; // percentage probability of chacter skipping a turn because of the status. 0 for no skip
	float defMultiplier; // multiplier for physical damage taken
	float mDefMultiplier; // multiplier for magical damage taken
	Status(std::string n, int dur, int dmg, int skip, float defMult, float mDefMult);
};