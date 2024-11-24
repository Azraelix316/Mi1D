#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <random>
using namespace std;
//Model 1: 11/24 Predicting Disease Outbreaks
//Main source: https://www.youtube.com/watch?v=m6Hr69JH_wA
//https://pmc.ncbi.nlm.nih.gov/articles/PMC3693038/#:~:text=Because%20the%20number%20of%20initially,(%20N%20%2D%201%20)%20)%20.
double susceptible=1000;
double infected=1;
double removed=0;
double b=0.0001;
double u=0.02;
int counter=0;
int main() {
//Solution 1: ODE
fstream fout;
fout.open("data.csv",ios::out);
double R0=b*susceptible*1/u;
        fout << "susceptible" << "," << "infected" <<","<< "removed" << ","<< "time" <<"\n";
    // while (infected>0 && counter<1000) {
    //     fout << susceptible << "," << infected <<","<< removed << "," << counter <<"\n";
    //     susceptible+=ceil(infected*-b*susceptible);
    //     infected+=ceil(susceptible*b*infected-u*infected);
    //     removed+=ceil(u*infected);
    //     counter++;
    // }
//Solution 2: ODE + Stochastic
    while (infected>0 && counter<1000) {
        fout << susceptible << "," << infected <<","<< removed << "," << counter <<"\n";
        //able to go from 0-2x infection, average is the same
        double randomInfected=rand()/32767.00*b*susceptible*infected*2;
        double randomRecovered=rand()/32767.00*u*infected*2;
        susceptible-=ceil(randomInfected);
        infected+=ceil(randomInfected-randomRecovered);
        removed+=ceil(randomRecovered);
        counter++;
    }

}