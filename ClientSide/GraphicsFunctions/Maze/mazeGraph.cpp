#include "mazeGraph.h"

using namespace std;

mazeGraph::mazeGraph()
{
}

bool mazeGraph::isConnected()
{
	vector<node> nodeQueue = { nodeList[0] };
	bool flag;
	int vectNum;
	while (true) {
		nodeQueue[0].visited = true;
		if (nodeQueue[0].connections == vector<sf::Vector2i>()) {
			break;
		}
		flag = false;
		for (sf::Vector2i i : nodeQueue[0].connections) {
			vectNum = i.y * 5 + i.x;
			if (!nodeList[vectNum].visited) {
				flag = true;
				nodeQueue.push_back(nodeList[vectNum]);
			}
		}
		if (!flag) {
			break;
		}

		nodeQueue.erase(nodeQueue.begin());

	}
	for (node i : nodeList) {
		if (!i.visited) {
			return false;
		}
	}
	return true;
}

void mazeGraph::addNode(node newNode) {
	nodeList.push_back(newNode);
}
