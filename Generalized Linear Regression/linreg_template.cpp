#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
using namespace std;

double residuals(vector<vector<string>> data, vector<double> coefficients,int dvColumn, vector<int> ivColumn) {
    double residual=0;
    for (int j = 0; j < data.size(); j++) {
        double current=0;
        for (int i = 0; i < coefficients.size()-1; i++) {
        current+=coefficients[i]*stod(data[j][ivColumn[i]]);
        }
        current+=coefficients[coefficients.size()];
        residual+=pow(stod(data[j][dvColumn])-current,2);
    }
    return residual;
}

int main() {
    const int stepSize = 1;
    int dvColumn;
    int coefficientSize;
    int ivColumn;
    cout << "N of coefficients? ";
    cin >> coefficientSize;
    cout << "DV Column? ";
    cin >> dvColumn;
    vector<double> coefficients(coefficientSize, 0.0);
    vector<int> ivColumns(coefficientSize, 0.0);
    for (int i=1;i<coefficientSize;i++) {
    cout << "IV Data Column Number " << i << " is? ";
    cin >> ivColumn;
    }
    fstream fin;
    fin.open("data.csv", ios::in);
    // data collection
    string row, temp, line, col;
    vector<vector<string>> data;
    vector<string> curr;
    while (getline(fin, line, '\n')) {
        stringstream s(line);
        // read every column and store it into col
        while (getline(s, col, ',')) {
            // add all the column data into a vector
            if (!col.empty()) {
                curr.push_back(col);
            } else {
                curr.push_back("0");
            }
        }
        data.push_back(curr);
        // pushes the vector into a 2d array data
        curr.clear();
    }
        double lastssqr;
        bool improvement=true;
        double trainingSpeed=1;
while (trainingSpeed>0.01) {
    improvement=true;
    while (improvement) {
        improvement=false;
    for (int j=0;j<coefficients.size();j++) {
        //calculates the last sum of squares to compare
        lastssqr=residuals(data,coefficients,dvColumn,ivColumns);
        coefficients[j]+=trainingSpeed;
        //modifies current coefficient up or down until it can't improve
        while (lastssqr>residuals(data,coefficients,dvColumn,ivColumns)) {
        lastssqr=residuals(data,coefficients,dvColumn,ivColumns);
        coefficients[j]+=trainingSpeed;
        //flags an improvement
        improvement=true;
        }
        //keeps coefficient the same
        coefficients[j]-=trainingSpeed;
        lastssqr=residuals(data,coefficients,dvColumn,ivColumns); 
        coefficients[j]-=trainingSpeed; 
        while (lastssqr>residuals(data,coefficients,dvColumn,ivColumns)) {
        lastssqr=residuals(data,coefficients,dvColumn,ivColumns);
        coefficients[j]-=trainingSpeed;
        //flags an improvement
        improvement=true;
        }
        //keeping coefficient the same
        coefficients[j]+=trainingSpeed;

        //ups training speed
        trainingSpeed+=trainingSpeed*0.01;
    }  
    } 
    //displays current coefficients and error, used to plug into excel to get r-squared, etc.
    cout << "\n" << residuals(data,coefficients,dvColumn,ivColumns) << "\n";
    for (int i=0;i<coefficients.size();i++) {
    cout << coefficients[i]<< ",";
    } 
    //halves training speed, to increase precision
    trainingSpeed=trainingSpeed/2.0;
    cout << "\n"<< "Training Speed:" << trainingSpeed << "\n";
}




}