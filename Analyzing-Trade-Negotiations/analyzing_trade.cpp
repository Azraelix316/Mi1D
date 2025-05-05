#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<vector<double>> read(string file) {
fstream fout;
    fout.open(file, ios::out);
    fstream fin;
    fin.open(file,ios::in);
    //data collection
    string row,temp,line,col;
    vector<vector<double>> data;
    vector<double> curr;
while (getline(fin,line,'\n')) {
    stringstream s(line);
        // read every column and store it into col
        while (getline(s,col,','))
        {
            // add all the column data into a vector
            if (!col.empty()) {
            curr.push_back(stod(col));
            } else {
curr.push_back(0);
            }
        }
            data.push_back(curr);
            //pushes the vector into a 2d array data
            curr.clear();

        }
return data;
}
int main()
{
vector<vector<double>> productivity_1=read("product_1.csv"); 
vector<vector<double>> productivity_2=read("product_2.csv");
vector<vector<double>> mats_to_1=read("mats_1.csv");
vector<vector<double>> mats_to_2=read("mats_2.csv");

}

