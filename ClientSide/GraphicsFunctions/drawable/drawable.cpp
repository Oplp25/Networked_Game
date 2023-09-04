#include "drawable.h"
#include<unordered_map>
#include <filesystem>
using namespace std;

void drawable::loadTextures()
{
	const filesystem::path cwd = filesystem::current_path();
	filesystem::path thisPath = cwd/imagePath;
	vector<filesystem::directory_entry> imageFiles; //Vector of all the files in the imagePath directory

	for (auto const& dir_entry : filesystem::directory_iterator{ thisPath }) {// looping through all of the files in the imagePath Directory
		imageFiles.push_back(dir_entry); //adding the files to the vector
	}
	unordered_map<int, filesystem::directory_entry> filesMap;// a map that stores all of the files, along with an integer that represents the integer at the end of the file name
	for (filesystem::directory_entry i : imageFiles) {//looping through the vector of files
		filesMap.insert(std::pair<int, filesystem::directory_entry>((int)(i.path().filename().string()[1])-(int)'0', i));//inserting each file into the map
	}
	for (int i = 1; i <= imageFiles.size(); i++) {//looping through the map
		textArray.push_back(sf::Texture());
		textArray[i-1].loadFromFile(filesMap[i].path().string());//inserting the textures in the correct order
	}
}

sf::Sprite drawable::draw() {
	if (textArray.empty()) {
		loadTextures();
	}
	sprite.setPosition(localPosition);
	return sprite;
}

void drawable::changeSpriteText(std::string textArgs)
{
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
}
