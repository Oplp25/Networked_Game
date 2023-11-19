#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>

using namespace std;

char h2 = '-';
char h3d = 'T';
char h3u = '⊥';
char c1 = '⌜';
char c2 = '⌝';
char c3 = '⌟';
char c4 = '⌞';
char h4 = '+';
char v2 = '|';
char v3r = '⊢';
char v3l = '⊣';
unordered_map<string,char> cellChars = {{"h2",h2},{"h3d",h3d},{"h3u",h3u},{"c1",c1},{"c2",c2},{"c3",c3},{"c4",c4},{"h4",h4},{"v2",v2},{"v3r",v3r},{"v3l",v3l}};
unordered_map<string,vector<int>> cellConns={{"h2",{2,4}},{"h3d",{2,3,4}},{"h3u",{1,2,4}},{"c1",{1,4}},{"c2",{1,2}},{"c3",{2,3}},{"c4",{3,4}},{"h4",{1,2,3,4}},{"v2",{1,3}},{"v3r",{1,2,3}},{"v3l",{1,3,4}}};
unordered_map<vector<int>,string> cellConnsReverse={{{2,4},"h2"},{{2,3,4},"h3d"},{{1,2,4},"h3u"},{{1,4},"c1"},{{1,2},"c2"},{{2,3},"c3"},{{3,4},"c4"},{{1,2,3,4},"h4"},{{1,3},"v2"},{{1,2,3},"v3r"},{{1,3,4},"v3l"}};
vector<vector<int>> combos = {{1,2},{1,3},{1,4},{2,3}{2,4},{3,4},{1,2,3},{1,2,4},{1,3,4},{2,3,4},{1,2,3,4}};
class cell{
    private:
        char symbol;
    public:
        vector<int> conns;// 1-up, 2-right, 3-down, 4-left
        vector<int> pos;//sf::Vector2f pos;
        string cellType;
        char draw(){
            return symbol;
        }
        string genNewCell(int pos){
            if(count(conns.begin(),conns.end(),pos)==0){
                return "n";
            }
            vector<string> connsList1;
            //create list of all cell types that connect with the cell on pos side
            for(vector<int> i:combos){
                if(count(i.begin(),i.end(),pos!=0)){
                    connsList1.push_back(cellConnsReverse[i]);
                }
            }
            //select random item from list
            default_random_engine randGen;
	        uniform_int_distribution<int> distX(1, connsList1.size());
	        randGen.seed(time(0));
	        int rolled = distX(randGen);
            //return that string
            return connsList1[rolled];
        }
        cell(string cType){
            cellType = cType;
            symbol = cellChars[cType];
            conns = cellConns[cType];
        }
        cell(){
            cellType = "h2";
            symbol = '-';
            conns = {2,4};
        }
};
int main(){
    cout<<combos.size()<<endl;
    cout<<cellConns.size()<<endl;
    vector<vector<cell>> cellList;
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){

        }

    }
    return 0;
}