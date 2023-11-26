#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>
#include <fcntl.h>
using namespace std;

vector<string> h2 = {"______","______","      "};

vector<string> h3d = {"______","__  __"," |  | "};

vector<string> h3u = {"_|  |_","______","      "};

vector<string> c1 = {" ____"," |  _"," |  | "};

vector<string> c2 = {"_____ ","__  | "," |  | "};

vector<string> c3 = {"_|  | ","____| ","      "};

vector<string> c4 = {" |  |_"," |____","      "};      

vector<string> h4 = {"_|  |_","_    _"," |  | "};

vector<string> v2 = {" |  | "," |  | "," |  | "};

vector<string> v3r = {" |  |_"," |   _"," |  | "};

vector<string> v3l = {"_|  | ","_   | "," |  | "};//11 symbols
unordered_map<string,vector<string>> cellstrings = {{"h2",h2},{"h3d",h3d},{"h3u",h3u},{"c1",c1},{"c2",c2},{"c3",c3},{"c4",c4},{"h4",h4},{"v2",v2},{"v3r",v3r},{"v3l",v3l}};
unordered_map<string,vector<int>> cellConns={{"h2",{2,4}},{"h3d",{2,3,4}},{"h3u",{1,2,4}},{"c1",{1,4}},{"c2",{1,2}},{"c3",{2,3}},{"c4",{3,4}},{"h4",{1,2,3,4}},{"v2",{1,3}},{"v3r",{1,2,3}},{"v3l",{1,3,4}}};
//unordered_map<vector<int>,string> cellConnsReverse={{{2,4},"h2"},{{2,3,4},"h3d"},{{1,2,4},"h3u"},{{1,4},"c1"},{{1,2},"c2"},{{2,3},"c3"},{{3,4},"c4"},{{1,2,3,4},"h4"},{{1,3},"v2"},{{1,2,3},"v3r"},{{1,3,4},"v3l"}};
vector<string> cellTypes = {"h2","h3d","h3u","c1","c2","c3","c4","h4","v2","v3r","v3l"};
vector<vector<int>> combos = {{1,2},{1,3},{1,4},{2,3},{2,4},{3,4},{1,2,3},{1,2,4},{1,3,4},{2,3,4},{1,2,3,4}};
vector<vector<int>> order = {{2,3},{1,3},{1,2},{1,1},{2,1},{3,1},{3,2},{3,3},{3,4},{2,4},{1,4},{0,4},{0,3},{0,2},{0,1},{0,0},{1,0},{2,0},{3,0},{4,0},{4,1},{4,2},{4,3},{4,4}};
//unordered_map<vector<int>,int> posEnum = {{vector<int>(0,1),1},{vector<int>(1,0),2},{vector<int>(0,-1),3},{vector<int>(-1,0),4}};

default_random_engine randGen;


class cell{
    private:
        vector<string> symbol;
    public:
        vector<int> conns;// 1-up, 2-right, 3-down, 4-left
        vector<int> pos;//sf::Vector2f pos;
        string cellType;
        string draw(int i){
            return symbol[i];
        }
        string genNewCell(int pos){
            if(count(conns.begin(),conns.end(),pos)==0){
                return "n";
            }
            vector<vector<int>> connsList1;
            //create list of all cell types that connect with the cell on pos side
            for(vector<int> i:combos){
                if(count(i.begin(),i.end(),pos)!=0){
                    connsList1.push_back(i);
                }
            }
            //select random item from list
	        uniform_int_distribution<int> distX(1, connsList1.size());
	        int rolled = distX(randGen);
            vector<int> rtn = connsList1[rolled];
            for(string i:cellTypes){
                if(cellConns[i] == rtn){
                    return i;
                }
            }
            return "h4";
            //return that string
        }
        cell(string cType, vector<int> posP){
            cellType = cType;
            symbol = cellstrings[cType];
            conns = cellConns[cType];
            pos = posP;
        }
        cell(){
            pos = {5,5};
            cellType = "e";
            symbol = {"OOO","OOO","OOO"};
            conns = {2,4};
        }
};
int main(){
	randGen.seed(time(0));
	cell aCell;
    vector<vector<cell>> cellList = {{cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()}};
    vector<cell> chooseList;
    cellList[2][2]=cell("h4",{2,2});
    for(vector<int> i:order){
        chooseList.clear();
        vector<int> a;
        vector<int> b;
        vector<int> c;
        vector<int> d;
        for(int j = 0;j<5;j++){
            for(int k = 0;k<5;k++){
                a = {j,k+1};
                b = {j,k-1};
                c = {j+1,k};
                d = {j-1,k};
                if ((a==i || b==i || c==i || d==i) && cellList[j][k].cellType!="e"){
                    chooseList.push_back(cellList[j][k]);
                }
            }
        }
        if(chooseList.size() == 0){
            cout<<"Error while parsing cell "<<i[0]<<" , "<<i[1]<<". ChooseList == 0"<<endl;
            exit(NULL);
        }
        uniform_int_distribution<int> distX(0, chooseList.size()-1);
        int rolled = distX(randGen);
        aCell = chooseList[rolled];
        if(aCell.pos[0] == 5 && aCell.pos[1] == 5){
            cout<<"Error while parsing cell "<<i[0]<<" , "<<i[1]<<". aCell.pos == {5,5}"<<endl;
            exit(NULL);
        }
        //int relation = posEnum[{i[0]-aCell.pos[0],i[1]-aCell.pos[1]}];
        int relation;
        cout<<"I: "<<i[0]<<" , "<<i[1]<<endl;
        cout<<"acell: "<<aCell.pos[0]<<" , "<<aCell.pos[1]<<endl;
        vector<int> comp = {i[0]-aCell.pos[0],i[1]-aCell.pos[1]};
        if(comp == vector<int>(0,1)){
            relation = 1;
        } else if(comp == vector<int>(1,0)){
            relation = 2;
        }else if(comp == vector<int>(0,-1)){
            relation = 3;
        } else{
            relation = 4;
        }
        cellList[i[0]][i[1]] = cell(aCell.genNewCell(relation),i);
    }
    for (vector<cell> i:cellList){
        for(cell k:i){
                cout<<k.cellType;
        }
        cout<<endl;
    }
    for (vector<cell> i:cellList){
        for(int j=0;j<3;j++){
            for(cell k:i){
                cout<<k.draw(j);
            }
            cout<<endl;
        }
    }
    
    return 0;
}