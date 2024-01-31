#pragma once
#include "node.h"
#include<vector>

class mazeGraph {
	private:
		std::vector<node> nodeList;
	public:
		mazeGraph();
		bool isConnected();
		void addNode(node newNode);
};