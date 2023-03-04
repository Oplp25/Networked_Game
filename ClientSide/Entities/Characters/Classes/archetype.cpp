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


/*Function to make an ability score check, it generates a random number between 1 and 20, the adds the ability score modifier to it, then returns that
If the roll is made with advantage, then the max of 2 dice rolls is added to the ability score modifier, then returned
If the roll is made with disadvantage, then the min of 2 dice rolls is added to the ability score modifier, then returned
If the character has proficiency with that save, then their proficiency binus is added to the final score, in addition to all of the above*/

int Archetype::makeSave(abilityScoresEnum ability, char hasAdvantage)
{
	int add = floor((abilityScores[ability]-10)/2);
	if (find(savesProficient.begin(),savesProficient.end(),ability)!=savesProficient.end()) {//if ability is in savesProficient
		add+=profBonus;
	}
	default_random_engine randGen;
	uniform_int_distribution<int> distX(1, 20);
	randGen.seed(time(0));
	int rolled = distX(randGen);
	int rolled2 = distX(randGen);
	if (hasAdvantage == 'n') {
		return rolled + add ;
	}
	else if (hasAdvantage == 'a') {
		return max(rolled,rolled2) + add;
	}
	return min(rolled, rolled2) + add;
}

/*Function to make an ability score check, it generates a random number between 1 and 20, the adds the ability score modifier to it, then returns that
If the roll is made with advantage, then the max of 2 dice rolls is added to the ability score modifier, then returned
If the roll is made with disadvantage, then the min of 2 dice rolls is added to the ability score modifier, then returned*/

int Archetype::makeCheck(abilityScoresEnum ability, char hasAdvantage)
{
	int add = floor((abilityScores[ability] - 10) / 2);
	default_random_engine randGen;
	uniform_int_distribution<int> distX(1, 20);
	randGen.seed(time(0));
	int rolled = distX(randGen);
	int rolled2 = distX(randGen);
	if (hasAdvantage == 'n') {
		return rolled+add;
	}
	else if (hasAdvantage == 'a') {
		return max(rolled, rolled2)+add;
	}
	return min(rolled, rolled2)+add;
}

void Archetype::gainXP(int xpGained)
{
	xp+=xpGained;
	if( (xp / 100) > level){
		levelUp();
	}
}

void Archetype::levelUp()
{
	level++;
	(this->*levelUpFuncs[level - 2])();//runs the corresponding level function from the level it just reached
	int i =  hpIncrease();
	hpMax += i;
	hpCurrent += i;

	//need to have something to increase stamina and mana as well
}

void Archetype::setScores()
{
	manaMax += characterRace.maxManaIncrease;
	staminaMax += characterRace.maxStaminaIncrease;
	hpMax = characterRace.maxHealthIncrease + hpIncrease();
	manaCurrent = manaMax;
	staminaCurrent = staminaMax;
	hpCurrent = hpMax;
	speed = characterRace.speed;
}

int Archetype::hpIncrease()
{
	default_random_engine randGen;
	uniform_int_distribution<int> distX(1, hitDiceType);
	randGen.seed(time(0));
	return distX(randGen);
}
