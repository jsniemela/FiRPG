#include "Status.h";

Status::Status(int n, int dur, int dmg, int skip, int dmgMult) 
	:name{n}, duration{dur}, damagePerTurn{dmg}, skipProbability{skip}, dmgMultiplier{dmgMult}
{

}