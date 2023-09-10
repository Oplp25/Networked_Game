#include "entity.h"
#include<filesystem>
#include<unordered_map>
#include<iostream>
using namespace std;
entity::entity()
{
	hpCurrent = 1;
	hpMax = 1;
}

void entity::move(char direction)
{
	if (!checkEnd(direction)) {
		return void();
	}
	if (direction == 'u') {
		localPosition.y -= speed;
	}
	else if (direction == 'd') {
		localPosition.y += speed;
	}
	else if (direction == 'r') {
		localPosition.x += speed;
	}
	else if (direction == 'l') {
		localPosition.x -= speed;
	}
}

void entity::switchTextArray(char direction)
{
	if (direction != entityCurrentDirection) {
		entityCurrentDirection = direction;
		if (direction == 'u') {
			textArray = listOfTexts[0];
			currentText = 0;
		}
		else if (direction == 'd') {
			textArray = listOfTexts[1];
			currentText = 0;
		}
		else if (direction == 'l') {
			textArray = listOfTexts[2];
			currentText = 0;
		}
		else if (direction == 'r') {
			textArray = listOfTexts[3];
			currentText = 0;
		}
		else if (direction == 's') {
			textArray = listOfTexts[4];
		}
	}
}

bool entity::checkEnd(char direction)
{
	
	if (direction == 'u' && localPosition.y - speed > 40) {
		return true;
	}
	if (direction == 'd' && localPosition.y + speed < 1040) {
		return true;
	}
	if (direction == 'r' && localPosition.x + speed < 1880) {
		return true;
	}
	if (direction == 'l' && localPosition.y - speed > 40) {
		return true;
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
		sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		sprite.setTexture(textArray[currentText]);
	}
	else if (textArgs == "still") {
		sprite.setTexture(listOfTexts[4][0]);
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
	const filesystem::path cwd = filesystem::current_path();
	filesystem::path thisPath;
	vector<filesystem::directory_entry> imageFiles;//Vector of all the files in the imagePath directory
	unordered_map<int, filesystem::directory_entry> filesMap;// a map that stores all of the files, along with an integer that represents the integer at the end of the file name
	unordered_map<int, string> mapping({ {0,"up"},{1,"down"},{2,"left"},{3,"right"},{4,"still"},{5,"misc"} });
	for (int i = 0; i < 6; i++) {
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
			listOfTexts[i][j-1].loadFromFile(filesMap[j].path().string());//inserting the textures in the correct order
		}
	}
	textArray = listOfTexts[4];//sets the first textArray to the still array, as the entity will start still
	currentText = 0;
}
