#pragma once

class Status
{
private:
	int name;
	int duration;
	int damagePerTurn; // damage that the character takes every turn, negative values for healing(?)
	int skipProbability; // percentage probability of chacter skipping a turn because of the status. 0 for no skip
	int dmgMultiplier; // positive values means character takes more damage and negative means less

public:
	Status(int n, int dur, int dmg, int skip, int dmgMult);
};