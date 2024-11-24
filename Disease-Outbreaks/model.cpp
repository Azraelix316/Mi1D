#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
using namespace std;
//Model 1: 11/24 Predicting Disease Outbreaks
//Main source: https://www.youtube.com/watch?v=m6Hr69JH_wA
//https://pmc.ncbi.nlm.nih.gov/articles/PMC3693038/#:~:text=Because%20the%20number%20of%20initially,(%20N%20%2D%201%20)%20)%20.
double susceptible=1000;
double infected=1;
double removed=0;
double b=0.0001;
double u=0.01;
int counter=0;
int main() {
//Solution 1: ODE
fstream fout;
fout.open("data.csv",ios::out);
        fout << "susceptible" << "," << "infected" <<","<< "removed" << ","<< "time" <<"\n";
    while (susceptible>0 && counter<1000) {
        fout << susceptible << "," << infected <<","<< removed << "," << counter <<"\n";
        susceptible+=infected*-b*susceptible;
        infected+=susceptible*b*infected-u*infected;
        removed+=u*infected;
        counter++;
    }


}