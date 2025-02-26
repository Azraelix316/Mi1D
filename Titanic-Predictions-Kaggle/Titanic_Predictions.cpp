#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ostream>
#include <random>
#include <sstream>
#include <vector>
using namespace std;
double cutoff = 0.5;
double penaltyCoefficient = 1.0;
const bool train=false;
// modified
// linreg
// template
// 13 coefficients, 2,3,4,5,7,8,9,10,12,15,16,17
// 0,-0.716648,0,0.189354,0,1.06152,-0.000701105,0.000918566,-3.97018e-07,0,0.11847,-0.0422502,0.285485,
double residuals(vector<vector<string>> data, vector<double> coefficients, int dvColumn, vector<int> ivColumn) {
    double residual = 0;
    for (int j = 0; j < data.size(); j++) {
        double current = 0;
        for (int i = 0; i < coefficients.size() - 1; i++) {
            current += coefficients[i] * stod(data[j][ivColumn[i]]);
        }
        current += coefficients[coefficients.size() - 1];
        residual += pow(stod(data[j][dvColumn]) - current, 2);
    }
    // for (int i = 0; i < coefficients.size(); i++) {
    //     residual += penaltyCoefficient * pow(coefficients[i], 2);
    // }
    return residual;
}

double cutoffed(vector<vector<string>> data, vector<double> coefficients, int dvColumn, vector<int> ivColumn) {
    double residual = 0;
    for (int j = 0; j < data.size(); j++) {
        double current = 0;
        for (int i = 0; i < coefficients.size() - 1; i++) {
            current += coefficients[i] * stod(data[j][ivColumn[i]]);
        }
        current += coefficients[coefficients.size() - 1];
        if (current > cutoff) {
            current = 1;
        } else {
            current = 0;
        }
        residual += pow(stod(data[j][dvColumn]) - current, 2);
    }     
    return residual;
}

// function
// to
// check
// if a
// string
// is a
// number
bool is_number(string line) {
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}
vector<double> run(vector<vector<string>> data, vector<double> coefficients, int dvColumn, vector<int> ivColumn) {
    vector<double> results;
    for (int j = 0; j < data.size(); j++) {
        double current = 0;
        for (int i = 0; i < coefficients.size() - 1; i++) {
            if (ivColumn[i] > 0) {
                current += coefficients[i] * stod(data[j][ivColumn[i] - 1]);
            } else {
                current += coefficients[i] * stod(data[j][ivColumn[i]]);
            }
        }
        current += coefficients[coefficients.size() - 1];
        results.push_back(current);
    }
    return results;
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
    //8 coefficients
    vector<double> coefficients{0.0887838,0.260064,0.264753,0,0,0.510364,0,-0.00187225,-0.031855,-0.0121758,0,0.000658244,0,0,0.051845,0.0196972,0.105509,0.169544,0,0.0202757};
    vector<int> ivColumns{3,4,5,6,7,8,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
    //4,5,8,10,11,16,17,18
    //8 good
    //4,5 good
    //5 very good, 8 very good
    //bias good
    //age useless??
    //16,17,18
    //10,11 good (large values)
    //16 coefficients
//0,-0.723929,0,0.229544,0,1.06152,-0.000701105,0.00766481,-3.97018e-07,0,0.126742,-0.106372,0.112683,0.285485
// //0.6 cutoff r-squared 0.538
//     for (int i = 1; i < coefficientSize; i++) {
//         int currentIV;
//         cout << "IV Data Column Number " << i << " is? ";
//         cin >> currentIV;
//         ivColumns.push_back(currentIV);
//     }
    fstream fout;
    fout.open("results.csv", ios::out);
    fstream fin;
    fin.open("train.csv", ios::in);
    // data
    // collection
    string row, temp, line, col;
    vector<vector<string>> data;
    vector<string> curr;
    while (getline(fin, line, '\n')) {
        stringstream s(line);
        // read every column and store it into col
        while (getline(s, col, ',')) {
            // add all the column data into a vector
            if (!col.empty() && is_number(col)) {
                curr.push_back(col);
            } else {
                if (col == "female") {
                    curr.push_back("1");
                } else {
                    curr.push_back("0");
                }
            }
        }
        data.push_back(curr);
        // pushes the vector into a 2d array data
        curr.clear();
    }
    double lastssqr;
    bool improvement = true;
    double trainingSpeed = 1;
    // double average = 0;
    // for (int i = 0; i < data.size(); i++) {
    //     average += stod(data[i][dvColumn]);
    // }
    // average *= 1 / data.size();
    // double rGuess;
    // for (int i = 0; i < data.size(); i++) {
    //     rGuess += pow(stod(data[i][dvColumn]) - average, 2);
    // }
    double rGuess=342;
    while (trainingSpeed > 0.00001 && train==true) {
        improvement = true;
        while (improvement) {
            improvement = false;
            for (int j = 0; j < coefficients.size(); j++) {
            
                lastssqr = residuals(data, coefficients, dvColumn, ivColumns);
                coefficients[j] += trainingSpeed;
                while (lastssqr > residuals(data, coefficients, dvColumn, ivColumns)) {
                    lastssqr = residuals(data, coefficients, dvColumn, ivColumns);
                    coefficients[j] += trainingSpeed;
                    // flags an improvement
                    improvement = true;
                }
                // keeps coefficient the same
                coefficients[j] -= trainingSpeed;
                lastssqr = residuals(data, coefficients, dvColumn, ivColumns);
                coefficients[j] -= trainingSpeed;
                while (lastssqr > residuals(data, coefficients, dvColumn, ivColumns)) {
                    lastssqr = residuals(data, coefficients, dvColumn, ivColumns);
                    coefficients[j] -= trainingSpeed;
                    // flags an improvement
                    improvement = true;
                }
                // keeping coefficient the same
                coefficients[j] += trainingSpeed;
                // ups training speed
                trainingSpeed += trainingSpeed * 0.01;
            }
        }
        double bestCutoff=0;
        double bestError=1000;
        for (int i=0;i<100;i++) {
        cutoff=i*0.01;
        if (cutoffed(data, coefficients, dvColumn, ivColumns)<=bestError) {
        bestCutoff=cutoff;
        bestError=cutoffed(data, coefficients, dvColumn, ivColumns);
        }
        }
        cutoff=bestCutoff;
        // displays current coefficients and error, used to plug into excel to
        // get r-squared, etc.
        cout << "\nError:" << residuals(data, coefficients, dvColumn, ivColumns) << "\n";
        for (int i = 0; i < coefficients.size(); i++) {
            cout << coefficients[i] << ",";
        }
        cout << "\nCutoffed:" << cutoffed(data, coefficients, dvColumn, ivColumns);
        // r-squared
        cout << "\nR-squared: " << 1 - (residuals(data, coefficients, dvColumn, ivColumns) / rGuess);
        // halves training speed, to increase precision
        trainingSpeed = trainingSpeed / 2.0;
        cout << "\nCutoff: " << cutoff;
        cout << "\n"
             << "Training Speed:" << trainingSpeed << "\n";
    }
    cout << "Cutoff training... \n";

        double bestCutoff=0;
        double bestError=1000;
        for (int i=0;i<400;i++) {
        cutoff=i*0.025;
        if (cutoffed(data, coefficients, dvColumn, ivColumns)<=bestError) {
        bestCutoff=cutoff;
        bestError=cutoffed(data, coefficients, dvColumn, ivColumns);
        }
        }
        cutoff=bestCutoff;
    data.clear();
    curr.clear();

    col = "0";
    cout << "Running...";
    fstream fin2;
    fin2.open("test.csv", ios::in);
    // second file input
    while (getline(fin2, line, '\n')) {
        stringstream s(line);
        // read every column and store it into col
        while (getline(s, col, ',')) {
            // add all the column data into a vector
            if (!col.empty() && is_number(col)) {
                curr.push_back(col);
            } else {
                if (col == "female") {
                    curr.push_back("1");
                } else {
                    curr.push_back("0");
                }
            }
        }
        data.push_back(curr);
        // pushes the vector into a 2d array data
        curr.clear();
    }
    fstream coefficientsOut;
    coefficientsOut.open("coefficients.csv", ios::app);
    for (int i = 0; i < coefficientSize; i++) {
        coefficientsOut << coefficients[i] << ",";
    }
    coefficientsOut << "\n Cutoff: " << cutoff << "\n";
    // also prints the passenger number
    vector<double> results = run(data, coefficients, dvColumn, ivColumns);
    for (int i = 0; i < results.size(); i++) {
        fout << data[i][0] << ",";
        if (results[i] > cutoff) {
            fout << 1;
        } else {
            fout << 0;
        }
        fout << "\n";
    }
}