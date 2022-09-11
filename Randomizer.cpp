#include "Randomizer.h"
#include <random>

/*
int Randomizer::randomizeInt(int startValue, int endValue)
{
	std::default_random_engine rd; // seed with random value
	std::uniform_int_distribution<int> randomInt(startValue, endValue);
	return randomInt(rd);
}
*/

int randomizeInt(int startValue, int endValue)
{
	std::random_device rd;
	std::uniform_int_distribution<int> randomInt(startValue, endValue);
	return randomInt(rd);
}