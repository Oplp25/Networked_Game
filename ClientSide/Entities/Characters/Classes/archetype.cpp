#include "archetype.h"
#include<random>

using namespace std;
void Archetype::usePrimary() {
	(this->primaryPointer)(this);
}
void Archetype::useSecondary() {
	(this->secondaryPointer)(this);
}
void Archetype::useDefensive() {
	(this->defensivePointer)(this);
}
void Archetype::useSpecial() {
	(this->specialPointer)(this);
}
void Archetype::useBuff() {
	(this->buffPointer)(this);
}
void Archetype::useUlt() {
	(this->ultPointer)(this);
}

int Archetype::makeSave(abilityScoresEnum ability, char hasAdvantage)
{
	default_random_engine randGen;
	uniform_int_distribution<int> distX(1, 20);
	randGen.seed(time(0));
	int rolled = distX(randGen);
	int rolled2 = distX(randGen);
	if (hasAdvantage == 'n') {
		return rolled;
	}
	else if (hasAdvantage == 'a') {
		return max(rolled,rolled2);
	}
	return min(rolled,rolled2)
}

int Archetype::makeCheck(abilityScoresEnum ability, char hasAdvantage)
{
	return 0;
}
