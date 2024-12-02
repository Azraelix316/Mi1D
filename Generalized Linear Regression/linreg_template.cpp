#include <ostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

int main() {
const int stepSize=1;
int dvColumn;
int coefficientSize;
cout << "N of coefficients? ";
cin >> coefficientSize;
cout << "DV Column? ";
cin >> dvColumn;
vector<double> coefficients(coefficientSize,0.0);
vector<int> ivColumns(coefficientSize,0.0);
}