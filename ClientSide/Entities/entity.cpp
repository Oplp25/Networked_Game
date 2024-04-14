#include "entity.h"
#include<filesystem>
#include<unordered_map>
#include<iostream>
using namespace std;
entity::entity()
{
	speed = 1;
	name = "d";
	hpCurrent = 1;
	hpMax = 1;
}

void entity::attack(entity &ent,int damage)
{
	//cout << name << " attacking " << ent.name << endl;
	attacking = true;
	char dir;
	if (ent.localPosition.x > localPosition.x) {
		dir = 'r';
	}
	else {
		dir = 'l';
	}

	ent.damageSelf(damage);
	switchTextArray('a',dir);
}

void entity::move(char direction, vector<vector<sf::Vector2f*>> collObjs,vector<vector<int>> tileLayout)
{
	if (!checkEnd(direction, 1, tileLayout)) {
		return void();
	}
	if (direction == 'u') {
		for (vector<sf::Vector2f*> i : collObjs) { if (*i[0] == tile && *i[1] != localPosition) { if (sf::Rect<float>(*i[1], sf::Vector2f(64, 64)).intersects(sf::Rect<float>(localPosition.x, localPosition.y - speed, 64, 64))) { return void(); } } }
		localPosition.y -= speed;
	}
	else if (direction == 'd') {
		for (vector<sf::Vector2f*> i : collObjs) { if (*i[0] == tile && *i[1] != localPosition) { if (sf::Rect<float>(*i[1], sf::Vector2f(64, 64)).intersects(sf::Rect<float>(localPosition.x, localPosition.y + speed, 64, 64))) { return void(); } } }
		localPosition.y += speed;
	}
	else if (direction == 'r') {
		for (vector<sf::Vector2f*> i : collObjs) {if (*i[0] == tile && *i[1] != localPosition) { if (sf::Rect<float>(*i[1], sf::Vector2f(64, 64)).intersects(sf::Rect<float>(localPosition.x + speed, localPosition.y, 64, 64))) { return void(); } } }
		localPosition.x += speed;
	}
	else if (direction == 'l') {
		for (vector<sf::Vector2f*> i : collObjs) { if (*i[0] == tile && *i[1] != localPosition) { if (sf::Rect<float>(*i[1], sf::Vector2f(64, 64)).intersects(sf::Rect<float>(localPosition.x - speed, localPosition.y, 64, 64))) { return void(); } } }
		localPosition.x -= speed;
	}
}

void entity::damageSelf(int damage)
{
	if (!damaged) {
		hpCurrent -= damage;
		sprite.setColor(sf::Color(255, 0, 0));
		damaged = true;
		if (hpCurrent <= 0) {
			death();
		}
	}
}

void entity::death()
{
}

int entity::getCurrentText() const
{
	return currentText;

}

void entity::switchTextArray(char direction, char d2, char d3)
{
	if (direction != entityCurrentDirection) {//if you are changing direction
		if (direction != 'a') {//if you are not attackin
			entityCurrentDirection = direction;
		}
		currentText = 0;//set the array to 0
		if (direction == 'u') {//up
			textArray = listOfTexts[0];
			sprite.setScale(1, 1);
		}
		else if (direction == 'd') {//down
			textArray = listOfTexts[1];
			sprite.setScale(1, 1);
		}
		else if (direction == 'r') {//right
			textArray = listOfTexts[2];
			sprite.setScale(1, 1);
		}
		else if (direction == 'l') {//left
			textArray = listOfTexts[2];
			sprite.setScale(-1, 1);//inverted right
		}
		else if (direction == 's') {//still
			textArray = listOfTexts[3];
			sprite.setScale(1, 1);
		}
		else if (direction == 'a') {
			if (d3 == ' '){
				d3 = entityCurrentDirection;
			}
			// order of listOfTexts: up, down, right, still, rightAttack, upRightAttack,downRightAttack
			if (d3 == 'r') {
				textArray = listOfTexts[4];
				sprite.setScale(1, 1);
			}else if (d3 == 'l') {
				textArray = listOfTexts[4];
				sprite.setScale(-1, 1);
			}else if (d3 == 'u') {
				textArray = listOfTexts[5];
				if (d2 == 'r') {
					sprite.setScale(1, 1);
				}
				else {
					sprite.setScale(-1, 1);
				}
			}
			else {//down
				textArray = listOfTexts[6];
				if (d2 == 'r') {
					sprite.setScale(1, 1);
				}
				else {
					sprite.setScale(-1, 1);
				}
			}
		}
		sprite.setTexture(textArray[currentText]);
	}
}


void entity::changeSpriteTextServer(string textArgs) {
	if (textArgs == "next") {
		currentText++;
		if (currentText >= textArray.size()) {
			currentText = 0;
		}
	}
	else if (textArgs == "still") {
		switchTextArrayServer('s');
	}
	else if (textArgs == "up") {
		switchTextArrayServer('u');
	}
	else if (textArgs == "down") {
		switchTextArrayServer('d');
	}
	else if (textArgs == "left") {
		switchTextArrayServer('l');
	}
	else if (textArgs == "right") {
		switchTextArrayServer('r');
	}
}
void entity::switchTextArrayServer(char direction) {
	if (direction != entityCurrentDirection) {//if you are changing direction
		if (direction != 'a') {//if you are not attackin
			entityCurrentDirection = direction;
		}
		currentText = 0;//set the array to 0
	}
}
bool entity::checkEnd(char direction,int nums,vector<vector<int>> tileLayout)
{
	float comparisonCoord; // the place the entity would be if it did the move
	//this variable is so that if you have multiple rectangles in one column or row, you do not get a false result
	sf::Uint16 limit;//the limit for how far a row or column has been checked

	//sets limit and comparisonCoord based on the direction that you are moving in
	if (direction == 'u') {
		comparisonCoord = localPosition.y - 32 - speed * nums; // starting position -32 to centre the coordinates, -speed*number of moves the entity will make
		limit = 65535;//(2^16)-1
	}
	else if (direction == 'd') {
		comparisonCoord = localPosition.y + 32 + speed * nums;
		limit = 0;
	}
	else if (direction == 'r') {
		comparisonCoord = localPosition.x + 32 + speed * nums;
		limit = 0;
	}
	else if (direction == 'l') {
		comparisonCoord = localPosition.x - 32 - speed * nums;
		limit = 65535;
	}

	for (vector<int> i : tileLayout) {// for each rectangle in the path
		//if the entity is going up, within the x coords of i, and  the y coord is less than the limit
		if (direction == 'u' && localPosition.x<i[0] + i[2] && localPosition.x>i[0] && i[1] < limit) {
			//if comparisonCoord is < the y coord, then it might be in another rectangle, or out of the path, so we set the limit lower, and go to the next iteration. 
			//if comparisonCoord is > the y cord, then it must be within the rectangle, as the entity is going up.
			if (comparisonCoord < i[1]) {
				limit = i[1];
			}
			else {
				return true;
			}
		}
		else if (direction == 'd' && localPosition.x<i[0] + i[2] && localPosition.x>i[0] && i[1] + i[3] > limit) {
			if (comparisonCoord > i[1] + i[3]) {
				limit = i[1] + i[3];
			}
			else {
				return true;
			}
		}
		else if (direction == 'r' && localPosition.y<i[1] + i[3] && localPosition.y>i[1] && i[0] + i[2] > limit) {
			if (comparisonCoord > i[0] + i[2]) {
				limit = i[0] + i[2];
			}
			else {
				return true;
			}
		}
		else if (direction == 'l' && localPosition.y<i[1] + i[3] && localPosition.y>i[1] && i[0] < limit) {
			if (comparisonCoord < i[0]) {
				limit = i[0];
			}
			else {
				return true;
			}
		}
	}
	return false;
}

void entity::changeSpriteText(string textArgs) {
	if (textArray.empty()) {
		loadTextures();
	}
	if (textArgs == "next") {
		currentText++;
		if (currentText >= textArray.size()) {
			currentText = 0;
		}
		sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));//so that only a 64x64 texture is displayed
		sprite.setTexture(textArray[currentText]);
	}
	else if (textArgs == "still") {
		sprite.setTexture(listOfTexts[3][0]);
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

void entity::loadTextures() {
	sprite.setOrigin(32, 32);
	const filesystem::path cwd = filesystem::current_path();
	filesystem::path thisPath;
	vector<filesystem::directory_entry> imageFiles;//Vector of all the files in the imagePath directory
	unordered_map<int, filesystem::directory_entry> filesMap;// a map that stores all of the files, along with an integer that represents the integer at the end of the file name
	unordered_map<int, string> mapping({ {0,"up"},{1,"down"},{2,"right"},{3,"still"},{4,"rightAttack"},{5,"upRightAttack"},{6,"downRightAttack"} });
	for (int i = 0; i < 7; i++) {
		imageFiles = {};//resets the imageFiles vector
		filesMap = {};//resets filesMap
		thisPath = cwd / imagePath / mapping[i];// sets the thisPath directory to the next folder to be looped through
		//cout << thisPath.string() << endl;
		for (auto const& dir_entry : filesystem::directory_iterator{ thisPath }) {// looping through all of the files in the thisPath Directory
			imageFiles.push_back(dir_entry);//adding the files to the vector
		}
		for (filesystem::directory_entry j : imageFiles) {//looping through the vector of files
			//cout << j.path().filename().string() << endl;
			filesMap.insert(std::pair<int, filesystem::directory_entry>((int)(j.path().filename().string()[1]) - (int)'0', j));//inserting each file into the map
		}
		for (int j= 1; j <= imageFiles.size(); j++) {//looping through the map
			listOfTexts[i].push_back(sf::Texture());
			if (!listOfTexts[i][j - 1].loadFromFile(filesMap[j].path().string())) {//inserting the textures in the correct order
				cout << j <<" : " << mapping[i] <<" : "<<name<< endl;
				cout << "Could not load file" << filesMap[j].path().string() << endl;
			}
		}
	}
	textArray = listOfTexts[3];//sets the first textArray to the still array, as the entity will start still
	currentText = 0;
}
