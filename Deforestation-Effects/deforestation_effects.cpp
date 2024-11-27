#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <random>

/* sources:
Data:  https://www.globalforestwatch.org/dashboards/global/
CO2/tree https://ecotree.green/en/how-much-co2-does-a-tree-absorb
growth/ppm https://factsonclimate.org/infographics/concentration-warming-relationship
co2/ppm https://en.wikipedia.org/wiki/Carbon_dioxide_in_Earth%27s_atmosphere#cite_note-16
tree density https://www.oregonmetro.gov/news/power-trees
*/
int main()
{
    std::fstream fout;

    fout.open("data.csv", std::ios::out);
    // inputs in data
    std::fstream fin;
    fin.open("treecover_loss__ha.csv", std::ios::in);
    // data collection
    std::string row, temp, line, col;
    std::vector<std::vector<std::string>> data;
    std::vector<std::string> curr;
    while (getline(fin, line, '\n'))
    {
        std::stringstream s(line);
        // read every column and store it into col
        while (getline(s, col, ','))
        {
            // add all the column data into a vector, 0 for nothing
            if (!col.empty())
            {
                curr.push_back(col);
            }
            else
            {
                curr.push_back("0");
            }
        }
        data.push_back(curr);
        // pushes the vector into a 2d array data
        curr.clear();
    }
    double current = 0;
    std::vector<double> treeLoss;
    for (int i = 2; i < data.size(); i++)
    {
        if (data[i - 1][1] == data[i][1])
        {
            current += stod(data[i - 1][2]);
        }
        else
        {
            treeLoss.push_back(current);
            current = 0;
        }
    }
    double trend = (treeLoss[1] - treeLoss[0]) / treeLoss.size();
    double intercept = treeLoss[0];
    double co2 = 0;           // ppm
    double tempPerCo2 = 0.01; // per ppm
    double tempGrowth = 0;
    double co2PerTree = 25; // kg
    double ppmPerKg = 1 / (7.82e+12);
    fout << "Year,Tree Loss, CO2 Growth,Temperature Growth";
    for (int i = 0; i < 60; i++)
    {
        intercept += trend;
        co2 += co2PerTree * intercept * ppmPerKg * 2.47105 * 100;
        tempGrowth = tempPerCo2 * co2;
        fout << "\n"
             << i + 2023 << "," << intercept << "," << co2 << "," << tempGrowth;
    }
}