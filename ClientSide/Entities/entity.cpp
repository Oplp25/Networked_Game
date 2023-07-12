#include "entity.h"
#include<filesystem>
#include<unordered_map>
using namespace std;
entity::entity()
{
}

void entity::switchTextArray(char direction)
{
	if (direction == 'u') {
		textArray = listOfTexts[0];
	}else if (direction == 'd') {
		textArray = listOfTexts[1];
	}
	else if (direction == 'l') {
		textArray = listOfTexts[2];
	}
	else {
		textArray = listOfTexts[3];
	}
}

vector<sf::Texture> entity::loadTextures() {
	const filesystem::path cwd = filesystem::current_path();
	filesystem::path thisPath;
	
	vector<filesystem::directory_entry> imageFiles;
	unordered_map<int, filesystem::directory_entry> filesMap;
	unordered_map<int, string> mapping({ {0,"up"},{1,"down"},{2,"left"},{3,"right"},{4,"misc"} });
	for (int i = 0; i < 3; i++) {
		thisPath = cwd / imagePath / mapping[i];
		for (auto const& dir_entry : filesystem::directory_iterator{ thisPath }) {
			imageFiles.push_back(dir_entry);
		}
		for (filesystem::directory_entry j : imageFiles) {
			filesMap.insert(std::pair<int, filesystem::directory_entry>((int)(j.path().filename().string()[-1]) - (int)'0', j));
		}
		for (int j= 1; j < imageFiles.size(); j++) {
			listOfTexts[i].push_back(sf::Texture());
			listOfTexts[i][j].loadFromFile(filesMap[j].path().string());
		}
	}
	textArray = listOfTexts[4];
	currentText = 0;
}
