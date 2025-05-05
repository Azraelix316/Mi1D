#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<vector<double>> read(string file) {
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
  double GDP_1,GDP_2;
  cout << "GDP of nation 1?";
  cin>>GDP_1;
  cout << "GDP of nation 2?";
  cin>>GDP_2;
vector<vector<double>> productivity_1=read("product_1.csv"); 
vector<vector<double>> productivity_2=read("product_2.csv");
vector<vector<double>> mats_to_1=read("mats_1.csv");
vector<vector<double>> mats_to_2=read("mats_2.csv");
double profit_1=0,profit_2=0;
for (int i = 0; i < productivity_1.size(); i++) {
  for (int j=0;j<productivity_1[i].size();j++) {
  profit_1+=productivity_1[i][j]*mats_to_1[i][j];
  }
}
for (int i = 0; i < productivity_2.size(); i++) {
  for (int j=0;j<productivity_2[i].size();j++) {
  profit_2+=productivity_2[i][j]*mats_to_2[i][j];
  }
}
std::cout << profit_1 << "\n" << profit_2;
double benefit1=profit_1/GDP_1;
double benefit2=profit_2/GDP_2;
double totalbenefit=(benefit1-benefit2)/benefit2;
std::cout<<"\n" << totalbenefit;
std::cout << std::flush;
}

