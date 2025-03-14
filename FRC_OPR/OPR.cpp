#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;


vector<vector<double>> residuals;


unordered_map<int, double> optimize(vector<vector<string>> data, unordered_map<int,double> TEAMS) {

return TEAMS;

}

int main()
{
    fstream fout;
    fout.open("data.csv", ios::out);
    fstream fin;
    fin.open("data.csv",ios::in);
    string row,temp,line,col;
    vector<vector<string>> data;
    vector<string> curr;
while (getline(fin,line,'\n')) {
    stringstream s(line);
        while (getline(s,col,','))
        {
            if (!col.empty()) {
            curr.push_back(col);
            } else {
curr.push_back("0");
            }
        }
            data.push_back(curr);
            curr.clear();
        }
unordered_map<int,int> TEAM_NUMBERS;


for (int i=0;i<data.size();i++) {
for (int j=0;j<data[i].size()-2;j++) {
if (TEAM_NUMBERS.find(stoi(data[i][j])) != TEAM_NUMBERS.end()) {
TEAM_NUMBERS[(stoi(data[i][j]))] = 0;
}
}
}



}
