#include "mazeFuncs.h"
#include "cell.h"

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

mazeGraph genGraph()
{
    mazeGraph ret;
    std::vector<std::vector<cell>> cellList;
    while(true){
        cellList = mazeGen();
        ret= mazeGraph();
        for (int i = 0; i < cellList.size(); i++) {
            for (int j = 0; j < cellList[i].size(); j++) {
                ret.addNode(node(cellList[i][j].conns, sf::Vector2i(j, i)));
            }
        }
        if (ret.isConnected()) {
            break;
        }
    }
    return mazeGraph();
}