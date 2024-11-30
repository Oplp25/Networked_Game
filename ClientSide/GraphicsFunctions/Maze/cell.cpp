#include "cell.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>
#include <fcntl.h>

using namespace std;

std::default_random_engine randGen;//set up engine
std::unordered_map<std::string, std::vector<int>> cellConns = { {"h2",{2,4}},{"h3d",{2,3,4}},{"h3u",{1,2,4}},{"c1",{2,3}},{"c2",{3,4}},{"c3",{1,4}},{"c4",{1,2}},{"h4",{1,2,3,4}},{"v2",{1,3}},{"v3r",{1,2,3}},{"v3l",{1,3,4}} };


vector<string> h2 = { "______","______","      " };

vector<string> h3d = { "______","__  __"," |  | " };

vector<string> h3u = { "_|  |_","______","      " };

vector<string> c1 = { " _____"," |  __"," |  | " };

vector<string> c2 = { "_____ ","__  | "," |  | " };

vector<string> c3 = { "_|  | ","____| ","      " };

vector<string> c4 = { " |  |_"," |____","      " };

vector<string> h4 = { "_|  |_","_    _"," |  | " };

vector<string> v2 = { " |  | "," |  | "," |  | " };

vector<string> v3r = { " |  |_"," |   _"," |  | " };

vector<string> v3l = { "_|  | ","__  | "," |  | " };

unordered_map<string, vector<string>> cellstrings = { {"h2",h2},{"h3d",h3d},{"h3u",h3u},{"c1",c1},{"c2",c2},{"c3",c3},{"c4",c4},{"h4",h4},{"v2",v2},{"v3r",v3r},{"v3l",v3l} };

string cell::draw(int i) {
    return symbol[i];
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
    uniform_int_distribution<int> distX(1, connsList1.size()-1);
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
    symbol = cellstrings[cType];
    pos = posP;
}
cell::cell() {
    pos = { 5,5 };
    cellType = "e";
    conns = { 2,4 };
}
