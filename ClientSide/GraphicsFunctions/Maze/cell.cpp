#include "cell.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>
#include <fcntl.h>

using namespace std;

std::default_random_engine randGen;
std::unordered_map<std::string, std::vector<int>> cellConns = { {"h2",{2,4}},{"h3d",{2,3,4}},{"h3u",{1,2,4}},{"c1",{2,3}},{"c2",{3,4}},{"c3",{1,4}},{"c4",{1,2}},{"h4",{1,2,3,4}},{"v2",{1,3}},{"v3r",{1,2,3}},{"v3l",{1,3,4}} };


string cell::draw(int i) {
    return string();
}
string cell::genNewCell(int relation) {
    int relop;//opposite side
    switch (relation) {
    case 1:relop = 3; break;
    case 2:relop = 4; break;
    case 3:relop = 1; break;
    case 4:relop = 2; break;
    };
    vector<int> connst = conns;
    connst.push_back(0);
    if (find(connst.begin(), connst.end(), relation) == connst.end()) {
        return "h4";// instead, could try and find another cell it is ajacent to
    }
    vector<vector<int>> connsList1;
    //create list of all cell types that connect with the cell on pos side
    vector<int> j;
    for (vector<int> i : combos) {
        j = i;
        j.push_back(0);
        if (find(j.begin(), j.end(), relop) != j.end()) {
            connsList1.push_back(i);
        }
    }
    //select random item from list
    uniform_int_distribution<int> distX(1, connsList1.size());
    int rolled = distX(randGen);
    vector<int> rtn = connsList1[rolled];
    for (string i : cellTypes) {
        if (cellConns[i] == rtn) {
            return i;
        }
    }
    return "h4";
}
cell::cell(string cType, sf::Vector2f posP) {
    cellType = cType;
    conns = cellConns[cType];
    pos = posP;
}
cell::cell() {
    pos = { 5,5 };
    cellType = "e";
    conns = { 2,4 };
}