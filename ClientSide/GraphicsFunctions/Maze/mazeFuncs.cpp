#include "mazeFuncs.h"
#include "cell.h"
#include "../Colours/colourConsts.h"
#include<iostream>

using namespace std;

vector<vector<cell>> mazeGen() {
    default_random_engine randGen;
    randGen.seed(time(0));
    cell aCell;
    vector<vector<cell>> cellList = { {cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()} };//cellList[y][x]
    vector<cell> chooseList;
    cellList[2][2] = cell("h4", { 2,2 });
    for (vector<int> i : order) {
        chooseList.clear();
        vector<int> a;
        vector<int> b;
        vector<int> c;
        vector<int> d;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                a = { j,k + 1 };
                b = { j,k - 1 };
                c = { j + 1,k };
                d = { j - 1,k };
                if ((a == i || b == i || c == i || d == i) && cellList[j][k].cellType != "e") {
                    chooseList.push_back(cellList[j][k]);
                }
            }
        }
        if (chooseList.size() == 0) {
            cout << "Error while parsing cell " << i[0] << " , " << i[1] << ". ChooseList == 0" << endl;
            exit(NULL);
        }
        uniform_int_distribution<int> distX(0, chooseList.size() - 1);
        int rolled = distX(randGen);
        aCell = chooseList[rolled];
        if (aCell.pos.x == 5 && aCell.pos.y == 5) {
            cout << "Error while parsing cell " << i[0] << " , " << i[1] << ". aCell.pos == {5,5}" << endl;
            exit(NULL);
        }
        int relation;
        vector<int> comp = { i[0] - static_cast<int>(aCell.pos.x),i[1] - static_cast<int>(aCell.pos.y) };
        if (comp[0] == 0 && comp[1] == 1) {//i is to the right of aCell
            relation = 2;
        }
        else if (comp[0] == 1 && comp[1] == 0) {//i is below of aCell
            relation = 3;
        }
        else if (comp[0] == 0 && comp[1] == -1) {//i is to the left of aCell
            relation = 4;
        }
        else {//i is above aCell 
            relation = 1;
        }
        cellList[i[0]][i[1]] = cell(aCell.genNewCell(relation), sf::Vector2f(i[0], i[1]));
    }
    return cellList;
}

mazeGraph genGraph()//returns the mazeGraph of a newly generated maze
{
    int iterations = 0;
    mazeGraph ret;
    std::vector<std::vector<cell>> cellList;
    while (true) {
        iterations++;
        cellList = mazeGen();
        ret = mazeGraph(cellList);
        for (int i = 0; i < cellList.size(); i++) {
            for (int j = 0; j < cellList[i].size(); j++) {
                ret.addNode(node(cellList[i][j].conns, sf::Vector2f(j, i)));
            }
        }
        ret.setConnections();
        if (ret.isConnected()) {
            break;
        }
    }
    return ret;
}



vector<sf::RectangleShape> getCellRects(sf::Vector2f pos, std::vector < sf::Vector2f > conns, sf::RenderWindow& win) {
    vector<vector<int>> connsSimp = {};
    vector<sf::RectangleShape> ret;

    for (sf::Vector2f i : conns) {
        connsSimp.push_back({ static_cast<int>(i.x - pos.x),static_cast<int>(i.y - pos.y) });
    }
    
    int width = win.getSize().x;
    int height = win.getSize().y;

    

    ret.push_back(sf::RectangleShape(sf::Vector2f(width, height)));
    ret[ret.size()-1].setPosition(sf::Vector2f(0, 0));
    ret[ret.size()-1].setFillColor(colours::cinereous);

    ret.push_back(sf::RectangleShape(sf::Vector2f(width / 3, height / 3)));
    ret[ret.size()-1].setFillColor(colours::hunterGreen);
    ret[ret.size()-1].setPosition(sf::Vector2f(width / 3, height / 3));

    for (vector<int> i : connsSimp) {
        ret.push_back(sf::RectangleShape(sf::Vector2f(width / 3, height / 3)));
        ret[ret.size()-1].setFillColor(colours::hunterGreen);
        ret[ret.size()-1].setPosition(sf::Vector2f(width / 3 + width/3 * i[0], height / 3 + height / 3 * i[1]));
    }            
    return ret;
}

std::vector<std::vector<int>> getCollisionRectangles(std::vector<sf::RectangleShape> backRects)
{
    vector<vector<int>> ret;
    vector<int> temp;
    backRects.erase(backRects.begin());
    for (sf::RectangleShape i : backRects) {
        ret.push_back({static_cast<int>(i.getPosition().x),static_cast<int>(i.getPosition().y),static_cast<int>(i.getSize().x),static_cast<int>(i.getSize().y) });

    }
    return ret;
}

sf::Vector2f checkMoveTile(sf::Vector2f charPos,node currNode, vector<int> backgroundDimensions) {
    vector<char> relativeConns;
    sf::Vector2f check;
    for (sf::Vector2f i : currNode.connections) {
        check = sf::Vector2f(i.x-currNode.pos.x,i.y-currNode.pos.y);
        if (check.x == 0 && check.y == -1) {
            relativeConns.push_back('u');
        }else if (check.x == 0 && check.y == 1) {
            relativeConns.push_back('d');
        }else if (check.x == 1 && check.y == 0) {
            relativeConns.push_back('r');
        }else if (check.x == -1 && check.y == 0) {
            relativeConns.push_back('l');
        }
    }
    if (charPos.y < 48) {
        for (char i : relativeConns) {
            if (i == 'u') {
                return sf::Vector2f(currNode.pos.x,currNode.pos.y - 1);
            }
        }
    }
    else if (charPos.y > backgroundDimensions[1] - 48) {
        for (char i : relativeConns) {
            if (i == 'd') {
                return  sf::Vector2f(currNode.pos.x,currNode.pos.y + 1);
            }
        }
    }
    else if (charPos.x < 48) {
        for (char i : relativeConns) {
            if (i == 'l') {
                return  sf::Vector2f(currNode.pos.x-1,currNode.pos.y);
            }
        }
    }
    else if (charPos.x > backgroundDimensions[0] - 48) {
        for (char i : relativeConns) {
            if (i == 'r') {
                return  sf::Vector2f(currNode.pos.x+1,currNode.pos.y);
            }
        }
    }
    return currNode.pos;
}