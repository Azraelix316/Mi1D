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
double cutoff = 0.6;
double penaltyCoefficient = 0.0;
// modified
// linreg
// template
//13 coefficients, 2,3,4,5,7,8,9,10,12,15,16,17
//0,-0.716648,0,0.189354,0,1.06152,-0.000701105,0.000918566,-3.97018e-07,0,0.11847,-0.0422502,0.285485,
double residuals(vector<vector<string>> data, vector<double> coefficients, int dvColumn, vector<int> ivColumn) {
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
    for (int i = 0; i < coefficients.size(); i++) {
        residual += penaltyCoefficient * pow(coefficients[i], 2);
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
    vector<double> coefficients{0,-0.716648,0,0.189354,0,1.06152,-0.000701105,0.000918566,-3.97018e-07,0,0.11847,-0.0422502,0.285485};
    vector<int> ivColumns{2,3,4,5,7,8,9,10,12,15,16,17};

    // for (int i = 1; i < coefficientSize; i++) {
    //     int currentIV;
    //     cout << "IV Data Column Number " << i << " is? ";
    //     cin >> currentIV;
    //     ivColumns.push_back(currentIV);
    // }
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
    double trainingSpeed = 0.0000001;
    double average = 0;
    for (int i = 0; i < data.size(); i++) {
        average += stod(data[i][dvColumn]);
    }
    average *= 1 / data.size();
    double rGuess;
    for (int i = 0; i < data.size(); i++) {
        rGuess += pow(stod(data[i][dvColumn]) - average, 2);
    }
    while (trainingSpeed > 0.0000000001) {
        improvement = true;
        while (improvement) {
            improvement = false;
            for (int j = 0; j < coefficients.size(); j++) {
                // calculates the last sum of squares to compare
                lastssqr = residuals(data, coefficients, dvColumn, ivColumns);
                coefficients[j] += trainingSpeed;
                // modifies current coefficient up or down until it can't
                // improve
                cutoff -= trainingSpeed;
                while (lastssqr > residuals(data, coefficients, dvColumn, ivColumns)) {
                    lastssqr = residuals(data, coefficients, dvColumn, ivColumns);
                    cutoff -= trainingSpeed;
                }
                cutoff += trainingSpeed;
                while (lastssqr > residuals(data, coefficients, dvColumn, ivColumns)) {
                    lastssqr = residuals(data, coefficients, dvColumn, ivColumns);
                    cutoff += trainingSpeed;
                }
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
        // displays current coefficients and error, used to plug into excel to
        // get r-squared, etc.
        cout << "\n" << residuals(data, coefficients, dvColumn, ivColumns) << "\n";
        for (int i = 0; i < coefficients.size(); i++) {
            cout << coefficients[i] << ",";
        }
        // r-squared
        cout << "\nR-squared: " << 1 - (residuals(data, coefficients, dvColumn, ivColumns) / rGuess);
        // halves training speed, to increase precision
        trainingSpeed = trainingSpeed / 2.0;
        cout << "\nCutoff: " << cutoff;
        cout << "\n"
             << "Training Speed:" << trainingSpeed << "\n";
    }
    data.clear();
    curr.clear();
    col = "0";
    cout << "testing";
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