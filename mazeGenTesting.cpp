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

vector<string> c1 = {" _____"," |  __"," |  | "};

vector<string> c2 = {"_____ ","__  | "," |  | "};

vector<string> c3 = {"_|  | ","____| ","      "};

vector<string> c4 = {" |  |_"," |____","      "};      

vector<string> h4 = {"_|  |_","_    _"," |  | "};

vector<string> v2 = {" |  | "," |  | "," |  | "};

vector<string> v3r = {" |  |_"," |   _"," |  | "};

vector<string> v3l = {"_|  | ","__  | "," |  | "};//11 symbols
 
unordered_map<string,vector<int>> cellConns={{"h2",{2,4}},{"h3d",{2,3,4}},{"h3u",{1,2,4}},{"c1",{2,3}},{"c2",{3,4}},{"c3",{1,4}},{"c4",{1,2}},{"h4",{1,2,3,4}},{"v2",{1,3}},{"v3r",{1,2,3}},{"v3l",{1,3,4}}};
vector<string> cellTypes = {"h2","h3d","h3u","c1","c2","c3","c4","h4","v2","v3r","v3l"};
vector<vector<int>> combos = {{1,2},{1,3},{1,4},{2,3},{2,4},{3,4},{1,2,3},{1,2,4},{1,3,4},{2,3,4},{1,2,3,4}};
vector<vector<int>> order = {{2,3},{1,3},{1,2},{1,1},{2,1},{3,1},{3,2},{3,3},{3,4},{2,4},{1,4},{0,4},{0,3},{0,2},{0,1},{0,0},{1,0},{2,0},{3,0},{4,0},{4,1},{4,2},{4,3},{4,4}};

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
        string genNewCell(int relation){
            int relop;//opposite side
            switch( relation){
                case 1:relop = 3;break;
                case 2:relop = 4;break;
                case 3:relop = 1;break;
                case 4:relop = 2;break;
            };
            vector<int> connst = conns;
            connst.push_back(0);
            /*cout<<"connst: ";
            for(int i: connst){
                cout<<i<<" , ";
            }cout<<endl;
            cout<<"Relation: "<<relation<<endl;
            cout<<"Relop: "<<relop<<endl;*/
            if(find(connst.begin(),connst.end(),relation) == connst.end()){
                return "h4";// instead, could try and find another cell it is ajacent to
            }
            vector<vector<int>> connsList1;
            //create list of all cell types that connect with the cell on pos side
            vector<int> j;
            for(vector<int> i:combos){
                j = i;
                j.push_back(0);
                if(find(j.begin(),j.end(),relop)!= j.end()){
                    connsList1.push_back(i);
                }
            }
            /*cout<<"connsList1: ";
            for(vector<int> i: connsList1){
                //cout<<"("<<i[0]<<" , "<<i[1]<<")"<<" , ";
            }cout<<endl;*/
            //select random item from list
	        uniform_int_distribution<int> distX(1, connsList1.size());
	        int rolled = distX(randGen);
            vector<int> rtn = connsList1[rolled];
            for(string i:cellTypes){
                if(cellConns[i] == rtn){
                    //cout<<"cellType: "<<i<<endl;
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
    vector<vector<cell>> cellList = {{cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()},{cell(),cell(),cell(),cell(),cell()}};//cellList[y][x]
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
        //cout<<"I: "<<i[0]<<" , "<<i[1]<<endl;
        //cout<<"acell: "<<aCell.pos[0]<<" , "<<aCell.pos[1]<<endl;
        vector<int> comp = {i[0]-aCell.pos[0],i[1]-aCell.pos[1]};
        if(comp [0] == 0 && comp[1] == 1){//i is to the right of aCell
            relation = 2;
        } else if(comp[0] == 1 && comp[1] == 0){//i is below of aCell
            relation = 3;
        }else if(comp[0] == 0 && comp[1] == -1){//i is to the left of aCell
            relation = 4;
        } else{//i is above aCell 
            relation = 1;
        }
        cellList[i[0]][i[1]] = cell(aCell.genNewCell(relation),i);
        //cout<<endl<<"------------------------------------------"<<endl<<endl;
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