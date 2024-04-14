#include "mazeGraph.h"

using namespace std;

mazeGraph::mazeGraph() 
{
}

mazeGraph::mazeGraph(std::vector<std::vector<cell>> cellListP){
	cellList = cellListP;
}

void mazeGraph::setConnections(){
	vector<int> toPop;
	node connectedTo;
	int vectNum;
	bool flag;
	int iter;
	for (int i = 0; i < nodeList.size();i++) {//loop through the nodeList
		toPop = {};
		for (int j =0; j < nodeList[i].connections.size(); j++) {//loop through the connections vector
			//if the connection is out of range
			if (nodeList[i].connections[j].x < 0 || nodeList[i].connections[j].x>4 || nodeList[i].connections[j].y < 0 || nodeList[i].connections[j].y>4) {
				toPop.push_back(j);
				continue;
			}
			vectNum = nodeList[i].connections[j].y * 5 + nodeList[i].connections[j].x;//generating the index in nodeList for the connection
			connectedTo = nodeList[vectNum];
			flag = false;
			for (sf::Vector2f k : connectedTo.connections) {
				if (k == nodeList[i].pos) {
					flag = true;
					break;
				}
			}
			if (!flag) {//if this node's position is not in that node's connections vector
				toPop.push_back(j);
			}
		}

		//remove any connection that has an index in toPop
		for (int j : toPop) {
			nodeList[i].connections[j] = sf::Vector2f(-1, -1);
		}
		for (iter = 0; iter < nodeList[i].connections.size();iter++) {
			if (nodeList[i].connections[iter] == sf::Vector2f(-1, -1)) {
				nodeList[i].connections.erase(nodeList[i].connections.begin() + iter);
				iter--;
			}
		}
	}
}

bool mazeGraph::isConnected()
{
	vector<node> nodeQueue = { nodeList[0] };//nodes to visit
	bool flag;
	int vectNum;
	vector<int> vists = {1};//nodes that have been visited
	for (int i = 0; i < 24; i++) {
		vists.push_back(0);
	}
	while (true) {
		if (nodeQueue[0].connections == vector<sf::Vector2f>()) {//if a node has no connections
			break;
		}
		for (sf::Vector2f i : nodeQueue[0].connections) {
			vectNum = i.y * 5 + i.x;// the index that node is in nodeList
			if (vists[vectNum] == 0) {//if not visited
				vists[vectNum] = 1;
				nodeQueue.push_back(nodeList[vectNum]);
			}
		}
		nodeQueue.erase(nodeQueue.begin());
		if (nodeQueue.size() == 0) {//if nodeQueue is empty
			break;
		}

	}
	//if every node has been visited.
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

void mazeGraph::printMaze() {
	for (vector<cell> i : cellList) {
		for (int j = 0; j < 3; j++) {
			for (cell k : i) {
				cout << k.draw(j);
			}
			cout << endl;
		}
	}
}

node mazeGraph::getNode(sf::Vector2f nodePos)
{
	return nodeList[nodePos.y * 5 + nodePos.x];
}