#include "character.h"
#include<random>
#include<iostream>

using namespace std;

void character::usePrimary() {
	invoke(this->primaryPointer, this);
}
void character::useSecondary() {
	(this->secondaryPointer)(this);
}
void character::useDefensive() {
	(this->defensivePointer)(this);
}
void character::useSpecial() {
	(this->specialPointer)(this);
}
void character::useBuff() {
	(this->buffPointer)(this);
}
void character::useUlt() {
	(this->ultPointer)(this);
}


/*Function to make an ability score check, it generates a random number between 1 and 20, the adds the ability score modifier to it, then returns that
If the roll is made with advantage, then the max of 2 dice rolls is added to the ability score modifier, then returned
If the roll is made with disadvantage, then the min of 2 dice rolls is added to the ability score modifier, then returned
If the character has proficiency with that save, then their proficiency binus is added to the final score, in addition to all of the above*/

int character::makeSave(abilityScoresEnum ability, char hasAdvantage)
{
	int add = floor((abilityScores[ability] - 10) / 2);
	if (find(savesProficient.begin(), savesProficient.end(), ability) != savesProficient.end()) {//if ability is in savesProficient
		add += profBonus;
	}
	default_random_engine randGen;
	uniform_int_distribution<int> distX(1, 20);
	randGen.seed(time(0));
	int rolled = distX(randGen);
	int rolled2 = distX(randGen);
	if (hasAdvantage == 'n') {
		return rolled + add;
	}
	else if (hasAdvantage == 'a') {
		return max(rolled, rolled2) + add;
	}
	return min(rolled, rolled2) + add;
}

/*Function to make an ability score check, it generates a random number between 1 and 20, the adds the ability score modifier to it, then returns that
If the roll is made with advantage, then the max of 2 dice rolls is added to the ability score modifier, then returned
If the roll is made with disadvantage, then the min of 2 dice rolls is added to the ability score modifier, then returned*/

int character::makeCheck(abilityScoresEnum ability, char hasAdvantage)
{
	int add = floor((abilityScores[ability] - 10) / 2);
	default_random_engine randGen;
	uniform_int_distribution<int> distX(1, 20);
	randGen.seed(time(0));
	int rolled = distX(randGen);
	int rolled2 = distX(randGen);
	if (hasAdvantage == 'n') {
		return rolled + add;
	}
	else if (hasAdvantage == 'a') {
		return max(rolled, rolled2) + add;
	}
	return min(rolled, rolled2) + add;
}

void character::gainXP(int xpGained)
{
	xp += xpGained;
	if ((xp / 100) > level) {
		levelUp();
	}
}

void character::levelUp()
{
	level++;
	std::invoke(levelUpFuncs[level-2],classPtr);//runs the corresponding level function from the level it just reached
	int i = hpIncrease();
	hpMax += i;
	hpCurrent += i;

	//need to have something to increase stamina and mana as well
}

void character::setScores(std::vector<abilityScoresEnum> abilityScoreUpgrades, int maxManaIncrease, int maxHealthIncrease, int maxStaminaIncrease, float rSpeed)
{

	manaMax += maxManaIncrease;
	staminaMax += maxStaminaIncrease;
	hpMax = maxHealthIncrease + hpIncrease();
	manaCurrent = manaMax;
	staminaCurrent = staminaMax;
	hpCurrent = hpMax;
	speed = rSpeed;
}

//For when you level up, your HP increases by a random amount dictated by your hit dice.
int character::hpIncrease()
{
	default_random_engine randGen;
	uniform_int_distribution<int> distX(1, hitDiceType);
	randGen.seed(time(0));
	return distX(randGen);
}

character::character(string thisRace, string thisClass, string name, char error)
{
	string thisClassL = thisClass;
	transform(thisClassL.begin(), thisClassL.end(), thisClassL.begin(), ::tolower);//making every letter lowercase
	if (thisClassL == "paladin") {
		paladinObj = paladin();
		classPtr = &paladinObj;
	}
	else {
		error = 'i';
	}
	if (error == 'n') {
		levelUpFuncs = classPtr->classLevelUpFuncs;
		className = classPtr->getClassName();
		hitDiceType = classPtr->getHitDiceType();
		charInventory = classPtr->getStartingEquipment();
	}

	if (thisRace == "dwarf") {
		characterRace = "dwarf";
		dwarf tempRace = dwarf();
		setScores(tempRace.abilityScoreUpgrades, tempRace.maxManaIncrease, tempRace.maxHealthIncrease, tempRace.maxStaminaIncrease, tempRace.speed);
	}//else
	//need to add ability pointers
	xp = 0;
	level = 0;
	characterName = name;	
	imagePath = "Resources\\Sprite Assets\\" + thisRace + " " + thisClass;
	currentWeapon = charInventory.weapons[0];
	localPosition = sf::Vector2f(0, 0);
	tile = { 0,0 };//Temporary, for testing
}

character::character(){}

void character::changeSpriteText(string textArgs) {
	currentWeapon.changeSpriteText(textArgs);
	if (textArray.empty()) {
		loadTextures();
	}
	if (textArgs == "next") {
		currentText++;
		if (currentText >= textArray.size()) {
			currentText = 0;
		}
		sprite.setTexture(textArray[currentText]);
	}
	else if (textArgs == "still") {
		sprite.setTexture(listOfTexts[4][0]);//
		switchTextArray('s');
	}
	else if (textArgs == "up") {
		switchTextArray('u');
	}
	else if (textArgs == "down") {
		switchTextArray('d');
	}
	else if (textArgs == "left") {
		switchTextArray('l');
	}
	else if (textArgs == "right") {
		switchTextArray('r');
	}
}

sf::Sprite character::draw() {
	if (textArray.empty()) {
		loadTextures();
	}
	sprite.setPosition(localPosition);
	currentWeapon.localPosition = localPosition;
	return sprite;
}