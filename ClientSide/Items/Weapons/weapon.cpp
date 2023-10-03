#include "weapon.h"
#include<filesystem>
#include<unordered_map>
#include<iostream>

using namespace std;

weapon::weapon(){
	name = "Blank";
	cost = 0;
	charges = 1;
	consumable = true;
	imagePath = "";
	damage = 0;
	cooldown = 0;
	reach = 0;
	hands = 0;
}

weapon::weapon(std::string pname, int pcost, int pcharges, std::string pimagePath, int pdamage, float pcooldown, int preach, int phands){
	name = pname;
	cost = pcost;
	charges = pcharges;
	consumable = true;
	imagePath = pimagePath;
	damage = pdamage;
	cooldown = pcooldown;
	reach = preach;
	hands = phands;

}
weapon::weapon(weaponTemplate stats){
	name = stats.name;
	cost = stats.cost;
	charges = stats.charges;
	consumable = true;
	imagePath = stats.imagePath;
	damage = stats.damage;
	cooldown = stats.cooldown;
	reach = stats.reach;
	hands = stats.hands;
}
void weapon::loadTextures() {
	sprite.setOrigin(32, 32);
	const filesystem::path cwd = filesystem::current_path();
	filesystem::path thisPath;

	vector<filesystem::directory_entry> imageFiles;//Vector of all the files in the imagePath directory
	unordered_map<int, filesystem::directory_entry> filesMap;// a map that stores all of the files, along with an integer that represents the integer at the end of the file name
	unordered_map<int, string> mapping({ {0,"up"},{1,"down"},{2,"right"},{3,"still"},{4,"rightAttack"},{5,"upRightAttack"},{6,"downRightAttack"} });
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
		for (int j = 1; j <= imageFiles.size(); j++) {//looping through the map
			listOfTexts[i].push_back(sf::Texture());
			listOfTexts[i][j - 1].loadFromFile(filesMap[j].path().string());//inserting the textures in the correct order
		}
	}
	textArray = listOfTexts[4];//sest the first textArray to the misc array, as the entity will start still
	currentText = 0;
}

void weapon::changeSpriteText(string textArgs) {
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

void weapon::switchTextArray(char direction)
{
	if (direction != itemCurrentDirection) {
		itemCurrentDirection = direction;
		if (direction == 'u') {
			textArray = listOfTexts[0];
			currentText = 0;
			sprite.setScale(1, 1);
		}
		else if (direction == 'd') {
			textArray = listOfTexts[1];
			currentText = 0;
			sprite.setScale(1, 1);
		}
		else if (direction == 'l') {
			textArray = listOfTexts[2];
			currentText = 0;
			sprite.setOrigin(32, 32);
			sprite.setScale(-1, 1);
			sprite.setOrigin(0, 0);
		}
		else if (direction == 'r') {
			textArray = listOfTexts[2];
			currentText = 0;
			sprite.setScale(1, 1);
		}
		else if (direction == 's') {
			textArray = listOfTexts[3];
			sprite.setScale(1, 1);
		}
	}
}