#include "character.h"
#include<random>
#include<iostream>

using namespace std;

void character::usePrimary(vector<enemy>& enemyArray) {
	int j = 0;
	float newDist = 0.0;
	float distSquared = INT_MAX;
	for (int i = 0; i < enemyArray.size(); i++) {
		newDist = pow(enemyArray[i].localPosition.x - localPosition.x, 2) + pow(enemyArray[i].localPosition.y - localPosition.y, 2);
		if (newDist > distSquared or distSquared == INT_MAX) {
			distSquared = newDist;
			j = i;
		}
	}
	if (distSquared <= currentWeapon.reach * currentWeapon.reach) {
		attack(enemyArray[j], currentWeapon.damage);
	}
	else {
		attack();
	}
}
void character::attack(entity& ent, int damage)
{
	ent.damageSelf(damage);
	attack();
}
void character::attack() {
	attacking = true;
	char dir = ' ';
	char xDir = ' ';
	float gradient = 0.5;//0.5tan(angle) where angle is the angle between the top and bottom bounds of the right or left attcak, compared to rightup or rightdown
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	//cout << mousePos.x << " , " << mousePos.y << endl;
	//cout << localPosition.x << " , " << localPosition.y << endl;
	if (mousePos.x > localPosition.x) {
		xDir = 'r';
		if (mousePos.y > gradient* (mousePos.x - localPosition.x) + localPosition.y) {
			dir = 'd';
		}
		else if (mousePos.y < -gradient * (mousePos.x - localPosition.x) + localPosition.y) {
			dir = 'u';
		}
		else {
			dir = xDir;
		}
	}
	else {
		xDir = 'l';
		if (mousePos.y < gradient * (mousePos.x - localPosition.x) + localPosition.y) {
			dir = 'd';
		}
		else if (mousePos.y > -gradient * (mousePos.x - localPosition.x) + localPosition.y) {
			dir = 'u';
		}
		else {
			dir = xDir;
		}
	}
	switchTextArray('a', xDir, dir);
	currentWeapon.switchTextArray('a', xDir, dir);
}
void character::useSecondary() {
	classPtr->secondary();
}
void character::useDefensive() {
	classPtr->defensive();
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
	hpMax += i;//increase hp
	hpCurrent += i;
}

void character::setScores(std::vector<abilityScoresEnum> abilityScoreUpgrades, int maxManaIncrease, int maxHealthIncrease, int maxStaminaIncrease, float rSpeed)
{

	manaMax += maxManaIncrease;
	staminaMax += maxStaminaIncrease;
	hpMax = 30 + maxHealthIncrease + hpIncrease();
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

character::character(string thisRace, string thisClass, string nameP, char error)
{
	string thisClassL = thisClass;
	transform(thisClassL.begin(), thisClassL.end(), thisClassL.begin(), ::tolower);//making every letter lowercase
	if (thisClassL == "paladin") {
		paladinObj = paladin();
		hitDiceType = paladinObj.getHitDiceType();
	}
	if (thisRace == "dwarf") {
		characterRace = "dwarf";
		dwarf tempRace = dwarf();
		setScores(tempRace.abilityScoreUpgrades, tempRace.maxManaIncrease, tempRace.maxHealthIncrease, tempRace.maxStaminaIncrease, tempRace.speed);
	}//else if for other races
	xp = 0;
	level = 0;
	characterName = nameP;	
	className = thisClass;
	name = characterName;
	imagePath = "Resources\\Sprite Assets\\" + thisRace + " " + thisClass;
	localPosition = sf::Vector2f(300, 300);
	tile = { 0,0 };//Temporary, for testing
}
void character::classSetUp() {
	string thisClassL = className;
	transform(thisClassL.begin(), thisClassL.end(), thisClassL.begin(), ::tolower);//making every letter lowercase
	if (thisClassL == "paladin") {
		classPtr = &paladinObj;
	}
	levelUpFuncs = classPtr->classLevelUpFuncs;
	className = classPtr->getClassName();
	charInventory = classPtr->getStartingEquipment();
	currentWeapon = charInventory.weapons[0];
	//ability pointers
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