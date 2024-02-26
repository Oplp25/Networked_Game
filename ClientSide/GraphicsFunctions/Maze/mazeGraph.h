#pragma once
#include "node.h"
#include "cell.h"
#include<vector>

class mazeGraph {
	private:
		std::vector<node> nodeList;
	public:
		std::vector<std::vector<cell>> cellList;
		mazeGraph();
		mazeGraph(std::vector<std::vector<cell>> cellListP);
		void setConnections();
		bool isConnected();
		void addNode(node newNode);
};