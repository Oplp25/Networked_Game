#include "drawable.h"
#include<unordered_map>
#include <filesystem>
using namespace std;

std::vector<sf::Texture> drawable::loadTextures()
{
	const filesystem::path cwd = filesystem::current_path();
	filesystem::path thisPath = cwd/imagePath;
	vector<filesystem::directory_entry> imageFiles;

	for (auto const& dir_entry : filesystem::directory_iterator{ thisPath }) {
		imageFiles.push_back(dir_entry);
	}
	unordered_map<int, filesystem::directory_entry> filesMap;
	for (filesystem::directory_entry i : imageFiles) {
		filesMap.insert(std::pair<int, filesystem::directory_entry>((int)(i.path().filename().string()[-1])-(int)'0', i));
	}
	for (int i = 1; i < imageFiles.size(); i++) {
		textArray.push_back(sf::Texture());
		textArray[-1].loadFromFile(filesMap[i].path().string());
	}
	return std::vector<sf::Texture>();
}

sf::Sprite drawable::draw() {
	if (textArray.empty()) {
		textArray = loadTextures();
	}
	return sprite;
}

void drawable::changeSpriteText(std::string textArgs)
{
	if (textArgs == "next") {
		currentText++;
		if (currentText >= textArray.size()) {
			currentText == 0;
		}
		sprite.setTexture(textArray[currentText]);
	}
}
