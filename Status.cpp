#include "Status.h"

Status::Status(std::string n, int dur, int dmg, int skip, float defMult, float mDefMult)
	:name{n}, duration{dur}, damagePerTurn{dmg}, skipProbability{skip}, defMultiplier{defMult}, mDefMultiplier{mDefMult}
{

}