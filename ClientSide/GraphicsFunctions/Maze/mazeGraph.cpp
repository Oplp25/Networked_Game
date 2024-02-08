#include "mazeGraph.h"

using namespace std;

mazeGraph::mazeGraph() 
{
}

mazeGraph::mazeGraph(std::vector<std::vector<cell>> cellListP){
	cellList = cellListP;
}

bool mazeGraph::isConnected()
{
	vector<node> nodeQueue = { nodeList[0] };
	bool flag;
	int vectNum;
	vector<int> vists = {1};
	for (int i = 0; i < 24; i++) {
		vists.push_back(0);
	}
	while (true) {
		if (nodeQueue[0].connections == vector<sf::Vector2i>()) {
			break;
		}
		flag = false;
		for (sf::Vector2i i : nodeQueue[0].connections) {
			if (i.x<5 && i.x>-1 && i.y<5 && i.y>-1) {
				vectNum = i.y * 5 + i.x;
				if (vists[vectNum] == 0) {
					flag = true;
					vists[vectNum] = 1;
					nodeQueue.push_back(nodeList[vectNum]);
				}
			}
		}
		if (!flag) {
			break;
		}

		nodeQueue.erase(nodeQueue.begin());

	}
	for (int i : vists) {
		if (i==0) {
			return false;
		}
	}
	return true;
}

void mazeGraph::addNode(node newNode) {
	nodeList.push_back(newNode);
}
